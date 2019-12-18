#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  dev; scalar_t__* alloc_devs; } ;
struct TYPE_5__ {scalar_t__ fd; } ;
struct vb2_plane {scalar_t__ length; scalar_t__ data_offset; TYPE_2__ m; scalar_t__ bytesused; } ;
struct vb2_buffer {int num_planes; TYPE_3__* planes; scalar_t__ copied_timestamp; struct vb2_queue* vb2_queue; } ;
struct dma_buf {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  planes ;
struct TYPE_4__ {scalar_t__ fd; } ;
struct TYPE_6__ {scalar_t__ min_length; scalar_t__ length; int dbuf_mapped; scalar_t__ data_offset; TYPE_1__ m; scalar_t__ bytesused; int /*<<< orphan*/ * mem_priv; struct dma_buf* dbuf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dma_buf*) ; 
 int PTR_ERR (void*) ; 
 int VB2_MAX_PLANES ; 
 int /*<<< orphan*/  __vb2_buf_dmabuf_put (struct vb2_buffer*) ; 
 int /*<<< orphan*/  __vb2_plane_dmabuf_put (struct vb2_buffer*,TYPE_3__*) ; 
 int /*<<< orphan*/  attach_dmabuf ; 
 int /*<<< orphan*/  buf_cleanup ; 
 int /*<<< orphan*/  buf_init ; 
 int /*<<< orphan*/  buf_prepare ; 
 int call_bufop (struct vb2_queue*,int /*<<< orphan*/ ,struct vb2_buffer*,struct vb2_plane*) ; 
 int call_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* call_ptr_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_buf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int call_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  call_void_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 struct dma_buf* dma_buf_get (scalar_t__) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  fill_vb2_buffer ; 
 int /*<<< orphan*/  map_dmabuf ; 
 int /*<<< orphan*/  memset (struct vb2_plane*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __prepare_dmabuf(struct vb2_buffer *vb)
{
	struct vb2_plane planes[VB2_MAX_PLANES];
	struct vb2_queue *q = vb->vb2_queue;
	void *mem_priv;
	unsigned int plane;
	int ret = 0;
	bool reacquired = vb->planes[0].mem_priv == NULL;

	memset(planes, 0, sizeof(planes[0]) * vb->num_planes);
	/* Copy relevant information provided by the userspace */
	ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
			 vb, planes);
	if (ret)
		return ret;

	for (plane = 0; plane < vb->num_planes; ++plane) {
		struct dma_buf *dbuf = dma_buf_get(planes[plane].m.fd);

		if (IS_ERR_OR_NULL(dbuf)) {
			dprintk(1, "invalid dmabuf fd for plane %d\n",
				plane);
			ret = -EINVAL;
			goto err;
		}

		/* use DMABUF size if length is not provided */
		if (planes[plane].length == 0)
			planes[plane].length = dbuf->size;

		if (planes[plane].length < vb->planes[plane].min_length) {
			dprintk(1, "invalid dmabuf length %u for plane %d, minimum length %u\n",
				planes[plane].length, plane,
				vb->planes[plane].min_length);
			dma_buf_put(dbuf);
			ret = -EINVAL;
			goto err;
		}

		/* Skip the plane if already verified */
		if (dbuf == vb->planes[plane].dbuf &&
			vb->planes[plane].length == planes[plane].length) {
			dma_buf_put(dbuf);
			continue;
		}

		dprintk(3, "buffer for plane %d changed\n", plane);

		if (!reacquired) {
			reacquired = true;
			vb->copied_timestamp = 0;
			call_void_vb_qop(vb, buf_cleanup, vb);
		}

		/* Release previously acquired memory if present */
		__vb2_plane_dmabuf_put(vb, &vb->planes[plane]);
		vb->planes[plane].bytesused = 0;
		vb->planes[plane].length = 0;
		vb->planes[plane].m.fd = 0;
		vb->planes[plane].data_offset = 0;

		/* Acquire each plane's memory */
		mem_priv = call_ptr_memop(vb, attach_dmabuf,
				q->alloc_devs[plane] ? : q->dev,
				dbuf, planes[plane].length, q->dma_dir);
		if (IS_ERR(mem_priv)) {
			dprintk(1, "failed to attach dmabuf\n");
			ret = PTR_ERR(mem_priv);
			dma_buf_put(dbuf);
			goto err;
		}

		vb->planes[plane].dbuf = dbuf;
		vb->planes[plane].mem_priv = mem_priv;
	}

	/*
	 * This pins the buffer(s) with dma_buf_map_attachment()). It's done
	 * here instead just before the DMA, while queueing the buffer(s) so
	 * userspace knows sooner rather than later if the dma-buf map fails.
	 */
	for (plane = 0; plane < vb->num_planes; ++plane) {
		if (vb->planes[plane].dbuf_mapped)
			continue;

		ret = call_memop(vb, map_dmabuf, vb->planes[plane].mem_priv);
		if (ret) {
			dprintk(1, "failed to map dmabuf for plane %d\n",
				plane);
			goto err;
		}
		vb->planes[plane].dbuf_mapped = 1;
	}

	/*
	 * Now that everything is in order, copy relevant information
	 * provided by userspace.
	 */
	for (plane = 0; plane < vb->num_planes; ++plane) {
		vb->planes[plane].bytesused = planes[plane].bytesused;
		vb->planes[plane].length = planes[plane].length;
		vb->planes[plane].m.fd = planes[plane].m.fd;
		vb->planes[plane].data_offset = planes[plane].data_offset;
	}

	if (reacquired) {
		/*
		 * Call driver-specific initialization on the newly acquired buffer,
		 * if provided.
		 */
		ret = call_vb_qop(vb, buf_init, vb);
		if (ret) {
			dprintk(1, "buffer initialization failed\n");
			goto err;
		}
	}

	ret = call_vb_qop(vb, buf_prepare, vb);
	if (ret) {
		dprintk(1, "buffer preparation failed\n");
		call_void_vb_qop(vb, buf_cleanup, vb);
		goto err;
	}

	return 0;
err:
	/* In case of errors, release planes that were already acquired */
	__vb2_buf_dmabuf_put(vb);

	return ret;
}
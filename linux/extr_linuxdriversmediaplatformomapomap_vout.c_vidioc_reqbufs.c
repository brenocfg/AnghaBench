#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {TYPE_1__** bufs; } ;
struct v4l2_requestbuffers {scalar_t__ type; scalar_t__ memory; unsigned int count; } ;
struct omap_vout_device {scalar_t__ vid; unsigned int buffer_allocated; scalar_t__ memory; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_queue; scalar_t__* buf_phy_addr; scalar_t__* buf_virt_addr; int /*<<< orphan*/  buffer_size; scalar_t__ mmap_count; scalar_t__ streaming; struct videobuf_queue vbq; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ memory; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ OMAP_VIDEO1 ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int video1_numbuffers ; 
 unsigned int video2_numbuffers ; 
 int /*<<< orphan*/  videobuf_mmap_free (struct videobuf_queue*) ; 
 int videobuf_reqbufs (struct videobuf_queue*,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int vidioc_reqbufs(struct file *file, void *fh,
			struct v4l2_requestbuffers *req)
{
	int ret = 0;
	unsigned int i, num_buffers = 0;
	struct omap_vout_device *vout = fh;
	struct videobuf_queue *q = &vout->vbq;

	if (req->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;
	/* if memory is not mmp or userptr
	   return error */
	if ((V4L2_MEMORY_MMAP != req->memory) &&
			(V4L2_MEMORY_USERPTR != req->memory))
		return -EINVAL;

	mutex_lock(&vout->lock);
	/* Cannot be requested when streaming is on */
	if (vout->streaming) {
		ret = -EBUSY;
		goto reqbuf_err;
	}

	/* If buffers are already allocated free them */
	if (q->bufs[0] && (V4L2_MEMORY_MMAP == q->bufs[0]->memory)) {
		if (vout->mmap_count) {
			ret = -EBUSY;
			goto reqbuf_err;
		}
		num_buffers = (vout->vid == OMAP_VIDEO1) ?
			video1_numbuffers : video2_numbuffers;
		for (i = num_buffers; i < vout->buffer_allocated; i++) {
			omap_vout_free_buffer(vout->buf_virt_addr[i],
					vout->buffer_size);
			vout->buf_virt_addr[i] = 0;
			vout->buf_phy_addr[i] = 0;
		}
		vout->buffer_allocated = num_buffers;
		videobuf_mmap_free(q);
	} else if (q->bufs[0] && (V4L2_MEMORY_USERPTR == q->bufs[0]->memory)) {
		if (vout->buffer_allocated) {
			videobuf_mmap_free(q);
			for (i = 0; i < vout->buffer_allocated; i++) {
				kfree(q->bufs[i]);
				q->bufs[i] = NULL;
			}
			vout->buffer_allocated = 0;
		}
	}

	/*store the memory type in data structure */
	vout->memory = req->memory;

	INIT_LIST_HEAD(&vout->dma_queue);

	/* call videobuf_reqbufs api */
	ret = videobuf_reqbufs(q, req);
	if (ret < 0)
		goto reqbuf_err;

	vout->buffer_allocated = req->count;

reqbuf_err:
	mutex_unlock(&vout->lock);
	return ret;
}
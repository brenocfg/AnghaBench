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
struct TYPE_4__ {struct sg_list* data; } ;
struct splice_desc {size_t total_len; unsigned int flags; TYPE_1__ u; int /*<<< orphan*/  pos; } ;
struct sg_list {scalar_t__ len; scalar_t__ n; scalar_t__ size; int /*<<< orphan*/  sg; } ;
struct port_buffer {int /*<<< orphan*/  sg; } ;
struct port {TYPE_3__* portdev; TYPE_2__* out_vq; } ;
struct pipe_inode_info {scalar_t__ nrbufs; } ;
struct file {int f_flags; struct port* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  vdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  __send_to_port (struct port*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct port_buffer*,int) ; 
 int /*<<< orphan*/  __splice_from_pipe (struct pipe_inode_info*,struct splice_desc*,int /*<<< orphan*/ ) ; 
 struct port_buffer* alloc_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_buf (struct port_buffer*,int) ; 
 scalar_t__ is_rproc_serial (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pipe_lock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  pipe_to_sg ; 
 int /*<<< orphan*/  pipe_unlock (struct pipe_inode_info*) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_port_writable (struct port*,int) ; 

__attribute__((used)) static ssize_t port_fops_splice_write(struct pipe_inode_info *pipe,
				      struct file *filp, loff_t *ppos,
				      size_t len, unsigned int flags)
{
	struct port *port = filp->private_data;
	struct sg_list sgl;
	ssize_t ret;
	struct port_buffer *buf;
	struct splice_desc sd = {
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.data = &sgl,
	};

	/*
	 * Rproc_serial does not yet support splice. To support splice
	 * pipe_to_sg() must allocate dma-buffers and copy content from
	 * regular pages to dma pages. And alloc_buf and free_buf must
	 * support allocating and freeing such a list of dma-buffers.
	 */
	if (is_rproc_serial(port->out_vq->vdev))
		return -EINVAL;

	/*
	 * pipe->nrbufs == 0 means there are no data to transfer,
	 * so this returns just 0 for no data.
	 */
	pipe_lock(pipe);
	if (!pipe->nrbufs) {
		ret = 0;
		goto error_out;
	}

	ret = wait_port_writable(port, filp->f_flags & O_NONBLOCK);
	if (ret < 0)
		goto error_out;

	buf = alloc_buf(port->portdev->vdev, 0, pipe->nrbufs);
	if (!buf) {
		ret = -ENOMEM;
		goto error_out;
	}

	sgl.n = 0;
	sgl.len = 0;
	sgl.size = pipe->nrbufs;
	sgl.sg = buf->sg;
	sg_init_table(sgl.sg, sgl.size);
	ret = __splice_from_pipe(pipe, &sd, pipe_to_sg);
	pipe_unlock(pipe);
	if (likely(ret > 0))
		ret = __send_to_port(port, buf->sg, sgl.n, sgl.len, buf, true);

	if (unlikely(ret <= 0))
		free_buf(buf, true);
	return ret;

error_out:
	pipe_unlock(pipe);
	return ret;
}
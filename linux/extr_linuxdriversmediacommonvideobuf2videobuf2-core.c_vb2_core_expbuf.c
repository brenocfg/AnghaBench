#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 unsigned int O_ACCMODE ; 
 int dma_buf_fd (struct dma_buf*,unsigned int) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned int,unsigned int,int) ; 
 int vb2_core_expbuf_dmabuf (struct vb2_queue*,unsigned int,unsigned int,unsigned int,unsigned int,struct dma_buf**) ; 

int vb2_core_expbuf(struct vb2_queue *q, int *fd, unsigned int type,
		    unsigned int index, unsigned int plane, unsigned int flags)
{
	struct dma_buf *dbuf;
	int ret;

	ret = vb2_core_expbuf_dmabuf(q, type, index, plane, flags, &dbuf);
	if (ret)
		return ret;

	ret = dma_buf_fd(dbuf, flags & ~O_ACCMODE);
	if (ret < 0) {
		dprintk(3, "buffer %d, plane %d failed to export (%d)\n",
			index, plane, ret);
		dma_buf_put(dbuf);
		return ret;
	}

	dprintk(3, "buffer %d, plane %d exported as %d descriptor\n",
		index, plane, ret);
	*fd = ret;

	return 0;
}
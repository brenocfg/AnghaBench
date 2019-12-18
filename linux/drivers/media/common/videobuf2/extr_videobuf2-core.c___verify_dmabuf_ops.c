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
struct vb2_queue {int io_modes; TYPE_1__* mem_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  unmap_dmabuf; int /*<<< orphan*/  map_dmabuf; int /*<<< orphan*/  detach_dmabuf; int /*<<< orphan*/  attach_dmabuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int VB2_DMABUF ; 

__attribute__((used)) static int __verify_dmabuf_ops(struct vb2_queue *q)
{
	if (!(q->io_modes & VB2_DMABUF) || !q->mem_ops->attach_dmabuf ||
	    !q->mem_ops->detach_dmabuf  || !q->mem_ops->map_dmabuf ||
	    !q->mem_ops->unmap_dmabuf)
		return -EINVAL;

	return 0;
}
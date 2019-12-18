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
struct TYPE_2__ {int /*<<< orphan*/  mmap; int /*<<< orphan*/  put; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int EINVAL ; 
 int VB2_MMAP ; 

__attribute__((used)) static int __verify_mmap_ops(struct vb2_queue *q)
{
	if (!(q->io_modes & VB2_MMAP) || !q->mem_ops->alloc ||
	    !q->mem_ops->put || !q->mem_ops->mmap)
		return -EINVAL;

	return 0;
}
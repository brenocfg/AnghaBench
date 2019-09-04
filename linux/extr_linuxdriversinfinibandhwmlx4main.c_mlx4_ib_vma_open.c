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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;

/* Variables and functions */

__attribute__((used)) static void  mlx4_ib_vma_open(struct vm_area_struct *area)
{
	/* vma_open is called when a new VMA is created on top of our VMA.
	 * This is done through either mremap flow or split_vma (usually due
	 * to mlock, madvise, munmap, etc.). We do not support a clone of the
	 * vma, as this VMA is strongly hardware related. Therefore we set the
	 * vm_ops of the newly created/cloned VMA to NULL, to prevent it from
	 * calling us again and trying to do incorrect actions. We assume that
	 * the original vma size is exactly a single page that there will be no
	 * "splitting" operations on.
	 */
	area->vm_ops = NULL;
}
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
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct msc_iter {struct msc* msc; } ;
struct msc {int /*<<< orphan*/  mmap_count; } ;
struct TYPE_2__ {struct msc_iter* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msc_mmap_open(struct vm_area_struct *vma)
{
	struct msc_iter *iter = vma->vm_file->private_data;
	struct msc *msc = iter->msc;

	atomic_inc(&msc->mmap_count);
}
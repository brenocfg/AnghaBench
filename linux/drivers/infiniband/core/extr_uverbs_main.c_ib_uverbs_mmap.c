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
struct vm_area_struct {int dummy; } ;
struct ib_uverbs_file {TYPE_3__* device; } ;
struct ib_ucontext {TYPE_2__* device; } ;
struct file {struct ib_uverbs_file* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  disassociate_srcu; } ;
struct TYPE_4__ {int (* mmap ) (struct ib_ucontext*,struct vm_area_struct*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_ucontext*) ; 
 int PTR_ERR (struct ib_ucontext*) ; 
 struct ib_ucontext* ib_uverbs_get_ucontext_file (struct ib_uverbs_file*) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int stub1 (struct ib_ucontext*,struct vm_area_struct*) ; 

__attribute__((used)) static int ib_uverbs_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct ib_uverbs_file *file = filp->private_data;
	struct ib_ucontext *ucontext;
	int ret = 0;
	int srcu_key;

	srcu_key = srcu_read_lock(&file->device->disassociate_srcu);
	ucontext = ib_uverbs_get_ucontext_file(file);
	if (IS_ERR(ucontext)) {
		ret = PTR_ERR(ucontext);
		goto out;
	}

	ret = ucontext->device->ops.mmap(ucontext, vma);
out:
	srcu_read_unlock(&file->device->disassociate_srcu, srcu_key);
	return ret;
}
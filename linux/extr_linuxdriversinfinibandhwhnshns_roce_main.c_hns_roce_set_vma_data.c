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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; struct hns_roce_vma_data* vm_private_data; } ;
struct list_head {int dummy; } ;
struct hns_roce_vma_data {int /*<<< orphan*/  list; int /*<<< orphan*/ * vma_list_mutex; struct vm_area_struct* vma; } ;
struct hns_roce_ucontext {int /*<<< orphan*/  vma_list_mutex; struct list_head vma_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hns_roce_vm_ops ; 
 struct hns_roce_vma_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_set_vma_data(struct vm_area_struct *vma,
				 struct hns_roce_ucontext *context)
{
	struct list_head *vma_head = &context->vma_list;
	struct hns_roce_vma_data *vma_data;

	vma_data = kzalloc(sizeof(*vma_data), GFP_KERNEL);
	if (!vma_data)
		return -ENOMEM;

	vma_data->vma = vma;
	vma_data->vma_list_mutex = &context->vma_list_mutex;
	vma->vm_private_data = vma_data;
	vma->vm_ops = &hns_roce_vm_ops;

	mutex_lock(&context->vma_list_mutex);
	list_add(&vma_data->list, vma_head);
	mutex_unlock(&context->vma_list_mutex);

	return 0;
}
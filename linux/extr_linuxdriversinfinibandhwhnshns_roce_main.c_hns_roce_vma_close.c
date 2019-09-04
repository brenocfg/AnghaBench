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
struct vm_area_struct {scalar_t__ vm_private_data; } ;
struct hns_roce_vma_data {int /*<<< orphan*/  vma_list_mutex; int /*<<< orphan*/  list; int /*<<< orphan*/ * vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hns_roce_vma_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_vma_close(struct vm_area_struct *vma)
{
	struct hns_roce_vma_data *vma_data;

	vma_data = (struct hns_roce_vma_data *)vma->vm_private_data;
	vma_data->vma = NULL;
	mutex_lock(vma_data->vma_list_mutex);
	list_del(&vma_data->list);
	mutex_unlock(vma_data->vma_list_mutex);
	kfree(vma_data);
}
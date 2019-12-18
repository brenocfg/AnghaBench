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
struct ras_ih_data {scalar_t__ inuse; int /*<<< orphan*/  ring; int /*<<< orphan*/  ih_work; } ;
struct ras_manager {struct ras_ih_data ih_data; } ;
struct ras_ih_if {int /*<<< orphan*/  head; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ras_manager* amdgpu_ras_find_obj (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ras_ih_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_obj (struct ras_manager*) ; 

int amdgpu_ras_interrupt_remove_handler(struct amdgpu_device *adev,
		struct ras_ih_if *info)
{
	struct ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	struct ras_ih_data *data;

	if (!obj)
		return -EINVAL;

	data = &obj->ih_data;
	if (data->inuse == 0)
		return 0;

	cancel_work_sync(&data->ih_work);

	kfree(data->ring);
	memset(data, 0, sizeof(*data));
	put_obj(obj);

	return 0;
}
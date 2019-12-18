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
struct ras_ih_data {scalar_t__ inuse; size_t wptr; int aligned_element_size; int ring_size; int /*<<< orphan*/  ih_work; int /*<<< orphan*/  element_size; int /*<<< orphan*/ * ring; } ;
struct ras_manager {struct ras_ih_data ih_data; } ;
struct ras_dispatch_if {int /*<<< orphan*/  entry; int /*<<< orphan*/  head; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ras_manager* amdgpu_ras_find_obj (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int amdgpu_ras_interrupt_dispatch(struct amdgpu_device *adev,
		struct ras_dispatch_if *info)
{
	struct ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	struct ras_ih_data *data = &obj->ih_data;

	if (!obj)
		return -EINVAL;

	if (data->inuse == 0)
		return 0;

	/* Might be overflow... */
	memcpy(&data->ring[data->wptr], info->entry,
			data->element_size);

	wmb();
	data->wptr = (data->aligned_element_size +
			data->wptr) % data->ring_size;

	schedule_work(&data->ih_work);

	return 0;
}
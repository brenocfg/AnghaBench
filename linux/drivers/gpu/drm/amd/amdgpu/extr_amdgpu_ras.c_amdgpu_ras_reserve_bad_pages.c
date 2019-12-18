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
typedef  int uint64_t ;
struct ras_err_handler_data {int last_reserved; int count; TYPE_1__* bps; } ;
struct amdgpu_ras {int /*<<< orphan*/  recovery_lock; struct ras_err_handler_data* eh_data; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_2__ {int bp; struct amdgpu_bo* bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_ras_reserve_vram (struct amdgpu_device*,int,int /*<<< orphan*/ ,struct amdgpu_bo**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int amdgpu_ras_reserve_bad_pages(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct ras_err_handler_data *data;
	uint64_t bp;
	struct amdgpu_bo *bo;
	int i;

	if (!con || !con->eh_data)
		return 0;

	mutex_lock(&con->recovery_lock);
	data = con->eh_data;
	if (!data)
		goto out;
	/* reserve vram at driver post stage. */
	for (i = data->last_reserved; i < data->count; i++) {
		bp = data->bps[i].bp;

		if (amdgpu_ras_reserve_vram(adev, bp << PAGE_SHIFT,
					PAGE_SIZE, &bo))
			DRM_ERROR("RAS ERROR: reserve vram %llx fail\n", bp);

		data->bps[i].bo = bo;
		data->last_reserved = i + 1;
	}
out:
	mutex_unlock(&con->recovery_lock);
	return 0;
}
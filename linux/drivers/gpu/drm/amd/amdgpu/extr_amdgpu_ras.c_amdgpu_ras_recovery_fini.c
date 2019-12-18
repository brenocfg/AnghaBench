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
struct ras_err_handler_data {struct ras_err_handler_data* bps; } ;
struct amdgpu_ras {int /*<<< orphan*/  recovery_lock; struct ras_err_handler_data* eh_data; int /*<<< orphan*/  recovery_work; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_release_bad_pages (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_save_bad_pages (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ras_err_handler_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ras_recovery_fini(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct ras_err_handler_data *data = con->eh_data;

	cancel_work_sync(&con->recovery_work);
	amdgpu_ras_save_bad_pages(adev);
	amdgpu_ras_release_bad_pages(adev);

	mutex_lock(&con->recovery_lock);
	con->eh_data = NULL;
	kfree(data->bps);
	kfree(data);
	mutex_unlock(&con->recovery_lock);

	return 0;
}
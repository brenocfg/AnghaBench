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
struct ras_err_handler_data {int dummy; } ;
struct amdgpu_ras {struct amdgpu_device* adev; int /*<<< orphan*/  in_recovery; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  recovery_lock; struct ras_err_handler_data* eh_data; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  amdgpu_ras_do_recovery ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_load_bad_pages (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_reserve_bad_pages (struct amdgpu_device*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ras_err_handler_data* kmalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ras_recovery_init(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct ras_err_handler_data **data = &con->eh_data;

	*data = kmalloc(sizeof(**data),
			GFP_KERNEL|__GFP_ZERO);
	if (!*data)
		return -ENOMEM;

	mutex_init(&con->recovery_lock);
	INIT_WORK(&con->recovery_work, amdgpu_ras_do_recovery);
	atomic_set(&con->in_recovery, 0);
	con->adev = adev;

	amdgpu_ras_load_bad_pages(adev);
	amdgpu_ras_reserve_bad_pages(adev);

	return 0;
}
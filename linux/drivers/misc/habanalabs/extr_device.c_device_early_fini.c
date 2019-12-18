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
struct hl_device {TYPE_1__* asic_funcs; int /*<<< orphan*/  cq_wq; int /*<<< orphan*/  eq_wq; int /*<<< orphan*/  hl_chip_info; int /*<<< orphan*/  idle_busy_ts_arr; int /*<<< orphan*/  kernel_cb_mgr; int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  send_cpu_message_lock; int /*<<< orphan*/  debug_lock; int /*<<< orphan*/  mmu_cache_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* early_fini ) (struct hl_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_asid_fini (struct hl_device*) ; 
 int /*<<< orphan*/  hl_cb_mgr_fini (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 

__attribute__((used)) static void device_early_fini(struct hl_device *hdev)
{
	mutex_destroy(&hdev->mmu_cache_lock);
	mutex_destroy(&hdev->debug_lock);
	mutex_destroy(&hdev->send_cpu_message_lock);

	mutex_destroy(&hdev->fpriv_list_lock);

	hl_cb_mgr_fini(hdev, &hdev->kernel_cb_mgr);

	kfree(hdev->idle_busy_ts_arr);
	kfree(hdev->hl_chip_info);

	destroy_workqueue(hdev->eq_wq);
	destroy_workqueue(hdev->cq_wq);

	hl_asid_fini(hdev);

	if (hdev->asic_funcs->early_fini)
		hdev->asic_funcs->early_fini(hdev);
}
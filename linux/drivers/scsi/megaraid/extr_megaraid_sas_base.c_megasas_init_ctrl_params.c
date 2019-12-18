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
struct megasas_instance {int issuepend_done; int flag_ieee; int unload; int disableOnlineCtrlReset; int smp_affinity_enable; int msix_load_balance; scalar_t__ adapter_type; int /*<<< orphan*/  work_init; scalar_t__ UnevenSpanSupport; scalar_t__ last_time; scalar_t__ flag; TYPE_1__* pdev; int /*<<< orphan*/  reset_mutex; int /*<<< orphan*/  completion_lock; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  mfi_pool_lock; int /*<<< orphan*/  crashdump_lock; int /*<<< orphan*/  abort_cmd_wait_q; int /*<<< orphan*/  int_cmd_wait_q; int /*<<< orphan*/  total_io_count; int /*<<< orphan*/  fw_outstanding; int /*<<< orphan*/  internal_reset_pending_q; int /*<<< orphan*/  cmd_pool; int /*<<< orphan*/  adprecovery; int /*<<< orphan*/  fw_crash_state; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEGASAS_HBA_OPERATIONAL ; 
 scalar_t__ MFI_SERIES ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0071SKINNY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0073SKINNY ; 
 int /*<<< orphan*/  UNAVAILABLE ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ megasas_dbg_lvl ; 
 int /*<<< orphan*/  megasas_fusion_ocr_wq ; 
 scalar_t__ megasas_poll_wait_aen ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_fw_state_change_wq ; 
 scalar_t__ smp_affinity_enable ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void megasas_init_ctrl_params(struct megasas_instance *instance)
{
	instance->fw_crash_state = UNAVAILABLE;

	megasas_poll_wait_aen = 0;
	instance->issuepend_done = 1;
	atomic_set(&instance->adprecovery, MEGASAS_HBA_OPERATIONAL);

	/*
	 * Initialize locks and queues
	 */
	INIT_LIST_HEAD(&instance->cmd_pool);
	INIT_LIST_HEAD(&instance->internal_reset_pending_q);

	atomic_set(&instance->fw_outstanding, 0);
	atomic64_set(&instance->total_io_count, 0);

	init_waitqueue_head(&instance->int_cmd_wait_q);
	init_waitqueue_head(&instance->abort_cmd_wait_q);

	spin_lock_init(&instance->crashdump_lock);
	spin_lock_init(&instance->mfi_pool_lock);
	spin_lock_init(&instance->hba_lock);
	spin_lock_init(&instance->stream_lock);
	spin_lock_init(&instance->completion_lock);

	mutex_init(&instance->reset_mutex);

	if ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
	    (instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY))
		instance->flag_ieee = 1;

	megasas_dbg_lvl = 0;
	instance->flag = 0;
	instance->unload = 1;
	instance->last_time = 0;
	instance->disableOnlineCtrlReset = 1;
	instance->UnevenSpanSupport = 0;
	instance->smp_affinity_enable = smp_affinity_enable ? true : false;
	instance->msix_load_balance = false;

	if (instance->adapter_type != MFI_SERIES)
		INIT_WORK(&instance->work_init, megasas_fusion_ocr_wq);
	else
		INIT_WORK(&instance->work_init, process_fw_state_change_wq);
}
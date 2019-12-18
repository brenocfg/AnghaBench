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
struct pqi_ctrl_info {int /*<<< orphan*/  max_msix_vectors; int /*<<< orphan*/  irq_mode; scalar_t__ ctrl_id; int /*<<< orphan*/  raid_bypass_retry_work; int /*<<< orphan*/  raid_bypass_retry_list_lock; int /*<<< orphan*/  raid_bypass_retry_list; int /*<<< orphan*/  block_requests_wait; int /*<<< orphan*/  sync_request_sem; int /*<<< orphan*/  ctrl_offline_work; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  update_time_work; int /*<<< orphan*/  rescan_work; int /*<<< orphan*/  num_interrupts; int /*<<< orphan*/  event_work; int /*<<< orphan*/  scsi_device_list_lock; int /*<<< orphan*/  scsi_device_list; int /*<<< orphan*/  ofa_mutex; int /*<<< orphan*/  lun_reset_mutex; int /*<<< orphan*/  scan_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_MODE_NONE ; 
 int /*<<< orphan*/  PQI_MAX_MSIX_VECTORS ; 
 int /*<<< orphan*/  PQI_RESERVED_IO_SLOTS_SYNCHRONOUS_REQUESTS ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct pqi_ctrl_info* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_controller_count ; 
 int /*<<< orphan*/  pqi_ctrl_offline_worker ; 
 int /*<<< orphan*/  pqi_event_worker ; 
 int /*<<< orphan*/  pqi_heartbeat_timer_handler ; 
 int /*<<< orphan*/  pqi_raid_bypass_retry_worker ; 
 int /*<<< orphan*/  pqi_rescan_worker ; 
 int /*<<< orphan*/  pqi_update_time_worker ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pqi_ctrl_info *pqi_alloc_ctrl_info(int numa_node)
{
	struct pqi_ctrl_info *ctrl_info;

	ctrl_info = kzalloc_node(sizeof(struct pqi_ctrl_info),
			GFP_KERNEL, numa_node);
	if (!ctrl_info)
		return NULL;

	mutex_init(&ctrl_info->scan_mutex);
	mutex_init(&ctrl_info->lun_reset_mutex);
	mutex_init(&ctrl_info->ofa_mutex);

	INIT_LIST_HEAD(&ctrl_info->scsi_device_list);
	spin_lock_init(&ctrl_info->scsi_device_list_lock);

	INIT_WORK(&ctrl_info->event_work, pqi_event_worker);
	atomic_set(&ctrl_info->num_interrupts, 0);

	INIT_DELAYED_WORK(&ctrl_info->rescan_work, pqi_rescan_worker);
	INIT_DELAYED_WORK(&ctrl_info->update_time_work, pqi_update_time_worker);

	timer_setup(&ctrl_info->heartbeat_timer, pqi_heartbeat_timer_handler, 0);
	INIT_WORK(&ctrl_info->ctrl_offline_work, pqi_ctrl_offline_worker);

	sema_init(&ctrl_info->sync_request_sem,
		PQI_RESERVED_IO_SLOTS_SYNCHRONOUS_REQUESTS);
	init_waitqueue_head(&ctrl_info->block_requests_wait);

	INIT_LIST_HEAD(&ctrl_info->raid_bypass_retry_list);
	spin_lock_init(&ctrl_info->raid_bypass_retry_list_lock);
	INIT_WORK(&ctrl_info->raid_bypass_retry_work,
		pqi_raid_bypass_retry_worker);

	ctrl_info->ctrl_id = atomic_inc_return(&pqi_controller_count) - 1;
	ctrl_info->irq_mode = IRQ_MODE_NONE;
	ctrl_info->max_msix_vectors = PQI_MAX_MSIX_VECTORS;

	return ctrl_info;
}
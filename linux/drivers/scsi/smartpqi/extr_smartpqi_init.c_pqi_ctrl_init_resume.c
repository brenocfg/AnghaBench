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
struct pqi_ctrl_info {int pqi_mode_enabled; int controller_online; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MODE_MSIX ; 
 int /*<<< orphan*/  PQI_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pqi_change_irq_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int pqi_create_admin_queues (struct pqi_ctrl_info*) ; 
 int pqi_create_queues (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_unblock_requests (struct pqi_ctrl_info*) ; 
 int pqi_enable_events (struct pqi_ctrl_info*) ; 
 int pqi_force_sis_mode (struct pqi_ctrl_info*) ; 
 int pqi_get_ctrl_product_details (struct pqi_ctrl_info*) ; 
 int pqi_process_config_table (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_reinit_queues (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_save_ctrl_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_scan_scsi_devices (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_schedule_update_time_worker (struct pqi_ctrl_info*) ; 
 int pqi_set_diag_rescan (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_start_heartbeat_timer (struct pqi_ctrl_info*) ; 
 int pqi_wait_for_pqi_mode_ready (struct pqi_ctrl_info*) ; 
 int pqi_write_driver_version_to_host_wellness (struct pqi_ctrl_info*) ; 
 int sis_get_ctrl_properties (struct pqi_ctrl_info*) ; 
 int sis_get_pqi_capabilities (struct pqi_ctrl_info*) ; 
 int sis_init_base_struct_addr (struct pqi_ctrl_info*) ; 
 int sis_wait_for_ctrl_ready_resume (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_ctrl_init_resume(struct pqi_ctrl_info *ctrl_info)
{
	int rc;

	rc = pqi_force_sis_mode(ctrl_info);
	if (rc)
		return rc;

	/*
	 * Wait until the controller is ready to start accepting SIS
	 * commands.
	 */
	rc = sis_wait_for_ctrl_ready_resume(ctrl_info);
	if (rc)
		return rc;

	/*
	 * Get the controller properties.  This allows us to determine
	 * whether or not it supports PQI mode.
	 */
	rc = sis_get_ctrl_properties(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller properties\n");
		return rc;
	}

	rc = sis_get_pqi_capabilities(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining controller capabilities\n");
		return rc;
	}

	/*
	 * If the function we are about to call succeeds, the
	 * controller will transition from legacy SIS mode
	 * into PQI mode.
	 */
	rc = sis_init_base_struct_addr(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error initializing PQI mode\n");
		return rc;
	}

	/* Wait for the controller to complete the SIS -> PQI transition. */
	rc = pqi_wait_for_pqi_mode_ready(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"transition to PQI mode failed\n");
		return rc;
	}

	/* From here on, we are running in PQI mode. */
	ctrl_info->pqi_mode_enabled = true;
	pqi_save_ctrl_mode(ctrl_info, PQI_MODE);

	pqi_reinit_queues(ctrl_info);

	rc = pqi_create_admin_queues(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating admin queues\n");
		return rc;
	}

	rc = pqi_create_queues(ctrl_info);
	if (rc)
		return rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_MSIX);

	ctrl_info->controller_online = true;
	pqi_ctrl_unblock_requests(ctrl_info);

	rc = pqi_process_config_table(ctrl_info);
	if (rc)
		return rc;

	pqi_start_heartbeat_timer(ctrl_info);

	rc = pqi_enable_events(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling events\n");
		return rc;
	}

	rc = pqi_get_ctrl_product_details(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining product detail\n");
		return rc;
	}

	rc = pqi_set_diag_rescan(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error enabling multi-lun rescan\n");
		return rc;
	}

	rc = pqi_write_driver_version_to_host_wellness(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error updating host wellness\n");
		return rc;
	}

	pqi_schedule_update_time_worker(ctrl_info);

	pqi_scan_scsi_devices(ctrl_info);

	return 0;
}
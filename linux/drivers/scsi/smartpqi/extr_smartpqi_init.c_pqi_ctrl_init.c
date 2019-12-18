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
struct pqi_ctrl_info {scalar_t__ max_outstanding_requests; int pqi_mode_enabled; scalar_t__ num_msix_vectors_enabled; scalar_t__ num_queue_groups; scalar_t__ max_msix_vectors; int controller_online; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MODE_MSIX ; 
 scalar_t__ PQI_MAX_OUTSTANDING_REQUESTS ; 
 scalar_t__ PQI_MAX_OUTSTANDING_REQUESTS_KDUMP ; 
 int /*<<< orphan*/  PQI_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pqi_alloc_admin_queues (struct pqi_ctrl_info*) ; 
 int pqi_alloc_error_buffer (struct pqi_ctrl_info*) ; 
 int pqi_alloc_io_resources (struct pqi_ctrl_info*) ; 
 int pqi_alloc_operational_queues (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_calculate_io_resources (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_calculate_queue_resources (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_change_irq_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int pqi_create_admin_queues (struct pqi_ctrl_info*) ; 
 int pqi_create_queues (struct pqi_ctrl_info*) ; 
 int pqi_enable_events (struct pqi_ctrl_info*) ; 
 int pqi_enable_msix_interrupts (struct pqi_ctrl_info*) ; 
 int pqi_force_sis_mode (struct pqi_ctrl_info*) ; 
 int pqi_get_ctrl_product_details (struct pqi_ctrl_info*) ; 
 int pqi_get_ctrl_serial_number (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_init_operational_queues (struct pqi_ctrl_info*) ; 
 int pqi_process_config_table (struct pqi_ctrl_info*) ; 
 int pqi_register_scsi (struct pqi_ctrl_info*) ; 
 int pqi_report_device_capability (struct pqi_ctrl_info*) ; 
 int pqi_request_irqs (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_save_ctrl_mode (struct pqi_ctrl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_scan_scsi_devices (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_schedule_update_time_worker (struct pqi_ctrl_info*) ; 
 int pqi_set_diag_rescan (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_start_heartbeat_timer (struct pqi_ctrl_info*) ; 
 int pqi_validate_device_capability (struct pqi_ctrl_info*) ; 
 int pqi_wait_for_pqi_mode_ready (struct pqi_ctrl_info*) ; 
 int pqi_write_driver_version_to_host_wellness (struct pqi_ctrl_info*) ; 
 scalar_t__ reset_devices ; 
 int sis_get_ctrl_properties (struct pqi_ctrl_info*) ; 
 int sis_get_pqi_capabilities (struct pqi_ctrl_info*) ; 
 int sis_init_base_struct_addr (struct pqi_ctrl_info*) ; 
 int sis_wait_for_ctrl_ready (struct pqi_ctrl_info*) ; 

__attribute__((used)) static int pqi_ctrl_init(struct pqi_ctrl_info *ctrl_info)
{
	int rc;

	rc = pqi_force_sis_mode(ctrl_info);
	if (rc)
		return rc;

	/*
	 * Wait until the controller is ready to start accepting SIS
	 * commands.
	 */
	rc = sis_wait_for_ctrl_ready(ctrl_info);
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

	if (reset_devices) {
		if (ctrl_info->max_outstanding_requests >
			PQI_MAX_OUTSTANDING_REQUESTS_KDUMP)
			ctrl_info->max_outstanding_requests =
					PQI_MAX_OUTSTANDING_REQUESTS_KDUMP;
	} else {
		if (ctrl_info->max_outstanding_requests >
			PQI_MAX_OUTSTANDING_REQUESTS)
			ctrl_info->max_outstanding_requests =
					PQI_MAX_OUTSTANDING_REQUESTS;
	}

	pqi_calculate_io_resources(ctrl_info);

	rc = pqi_alloc_error_buffer(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate PQI error buffer\n");
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

	rc = pqi_alloc_admin_queues(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate admin queues\n");
		return rc;
	}

	rc = pqi_create_admin_queues(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error creating admin queues\n");
		return rc;
	}

	rc = pqi_report_device_capability(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"obtaining device capability failed\n");
		return rc;
	}

	rc = pqi_validate_device_capability(ctrl_info);
	if (rc)
		return rc;

	pqi_calculate_queue_resources(ctrl_info);

	rc = pqi_enable_msix_interrupts(ctrl_info);
	if (rc)
		return rc;

	if (ctrl_info->num_msix_vectors_enabled < ctrl_info->num_queue_groups) {
		ctrl_info->max_msix_vectors =
			ctrl_info->num_msix_vectors_enabled;
		pqi_calculate_queue_resources(ctrl_info);
	}

	rc = pqi_alloc_io_resources(ctrl_info);
	if (rc)
		return rc;

	rc = pqi_alloc_operational_queues(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to allocate operational queues\n");
		return rc;
	}

	pqi_init_operational_queues(ctrl_info);

	rc = pqi_request_irqs(ctrl_info);
	if (rc)
		return rc;

	rc = pqi_create_queues(ctrl_info);
	if (rc)
		return rc;

	pqi_change_irq_mode(ctrl_info, IRQ_MODE_MSIX);

	ctrl_info->controller_online = true;

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

	/* Register with the SCSI subsystem. */
	rc = pqi_register_scsi(ctrl_info);
	if (rc)
		return rc;

	rc = pqi_get_ctrl_product_details(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining product details\n");
		return rc;
	}

	rc = pqi_get_ctrl_serial_number(ctrl_info);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"error obtaining ctrl serial number\n");
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
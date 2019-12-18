#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int status; } ;
struct pm8001_hba_info {int controller_fatal_error; TYPE_2__ encrypt_info; TYPE_1__* chip; } ;
struct TYPE_3__ {scalar_t__ encrypt; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ PM8001_MAX_SPCV_INB_NUM ; 
 scalar_t__ PM8001_MAX_SPCV_OUTB_NUM ; 
 int check_fw_ready (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  init_default_table_values (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  init_pci_device_addresses (struct pm8001_hba_info*) ; 
 scalar_t__ mpi_init_check (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int /*<<< orphan*/  pm80xx_encrypt_update (struct pm8001_hba_info*) ; 
 int pm80xx_get_encrypt_info (struct pm8001_hba_info*) ; 
 int pm80xx_set_sas_protocol_timer_config (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_general_status_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_inbnd_queue_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_main_config_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_outbnd_queue_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_phy_attr_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  update_inbnd_queue_table (struct pm8001_hba_info*,scalar_t__) ; 
 int /*<<< orphan*/  update_main_config_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  update_outbnd_queue_table (struct pm8001_hba_info*,scalar_t__) ; 

__attribute__((used)) static int pm80xx_chip_init(struct pm8001_hba_info *pm8001_ha)
{
	int ret;
	u8 i = 0;

	/* check the firmware status */
	if (-1 == check_fw_ready(pm8001_ha)) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Firmware is not ready!\n"));
		return -EBUSY;
	}

	/* Initialize the controller fatal error flag */
	pm8001_ha->controller_fatal_error = false;

	/* Initialize pci space address eg: mpi offset */
	init_pci_device_addresses(pm8001_ha);
	init_default_table_values(pm8001_ha);
	read_main_config_table(pm8001_ha);
	read_general_status_table(pm8001_ha);
	read_inbnd_queue_table(pm8001_ha);
	read_outbnd_queue_table(pm8001_ha);
	read_phy_attr_table(pm8001_ha);

	/* update main config table ,inbound table and outbound table */
	update_main_config_table(pm8001_ha);
	for (i = 0; i < PM8001_MAX_SPCV_INB_NUM; i++)
		update_inbnd_queue_table(pm8001_ha, i);
	for (i = 0; i < PM8001_MAX_SPCV_OUTB_NUM; i++)
		update_outbnd_queue_table(pm8001_ha, i);

	/* notify firmware update finished and check initialization status */
	if (0 == mpi_init_check(pm8001_ha)) {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("MPI initialize successful!\n"));
	} else
		return -EBUSY;

	/* send SAS protocol timer configuration page to FW */
	ret = pm80xx_set_sas_protocol_timer_config(pm8001_ha);

	/* Check for encryption */
	if (pm8001_ha->chip->encrypt) {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("Checking for encryption\n"));
		ret = pm80xx_get_encrypt_info(pm8001_ha);
		if (ret == -1) {
			PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("Encryption error !!\n"));
			if (pm8001_ha->encrypt_info.status == 0x81) {
				PM8001_INIT_DBG(pm8001_ha, pm8001_printk(
					"Encryption enabled with error."
					"Saving encryption key to flash\n"));
				pm80xx_encrypt_update(pm8001_ha);
			}
		}
	}
	return 0;
}
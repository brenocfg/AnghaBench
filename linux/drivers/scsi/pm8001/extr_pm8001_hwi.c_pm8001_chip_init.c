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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct pm8001_hba_info {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GSM_SM_BASE ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ PM8001_MAX_INB_NUM ; 
 scalar_t__ PM8001_MAX_OUTB_NUM ; 
 int check_fw_ready (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  init_default_table_values (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  init_pci_device_addresses (struct pm8001_hba_info*) ; 
 scalar_t__ mpi_init_check (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  mpi_set_open_retry_interval_reg (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  mpi_set_phys_g3_with_ssc (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int,int) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  read_general_status_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_inbnd_queue_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_main_config_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  read_outbnd_queue_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  update_inbnd_queue_table (struct pm8001_hba_info*,scalar_t__) ; 
 int /*<<< orphan*/  update_main_config_table (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  update_outbnd_queue_table (struct pm8001_hba_info*,scalar_t__) ; 

__attribute__((used)) static int pm8001_chip_init(struct pm8001_hba_info *pm8001_ha)
{
	u8 i = 0;
	u16 deviceid;
	pci_read_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	/* 8081 controllers need BAR shift to access MPI space
	* as this is shared with BIOS data */
	if (deviceid == 0x8081 || deviceid == 0x0042) {
		if (-1 == pm8001_bar4_shift(pm8001_ha, GSM_SM_BASE)) {
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("Shift Bar4 to 0x%x failed\n",
					GSM_SM_BASE));
			return -1;
		}
	}
	/* check the firmware status */
	if (-1 == check_fw_ready(pm8001_ha)) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Firmware is not ready!\n"));
		return -EBUSY;
	}

	/* Initialize pci space address eg: mpi offset */
	init_pci_device_addresses(pm8001_ha);
	init_default_table_values(pm8001_ha);
	read_main_config_table(pm8001_ha);
	read_general_status_table(pm8001_ha);
	read_inbnd_queue_table(pm8001_ha);
	read_outbnd_queue_table(pm8001_ha);
	/* update main config table ,inbound table and outbound table */
	update_main_config_table(pm8001_ha);
	for (i = 0; i < PM8001_MAX_INB_NUM; i++)
		update_inbnd_queue_table(pm8001_ha, i);
	for (i = 0; i < PM8001_MAX_OUTB_NUM; i++)
		update_outbnd_queue_table(pm8001_ha, i);
	/* 8081 controller donot require these operations */
	if (deviceid != 0x8081 && deviceid != 0x0042) {
		mpi_set_phys_g3_with_ssc(pm8001_ha, 0);
		/* 7->130ms, 34->500ms, 119->1.5s */
		mpi_set_open_retry_interval_reg(pm8001_ha, 119);
	}
	/* notify firmware update finished and check initialization status */
	if (0 == mpi_init_check(pm8001_ha)) {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("MPI initialize successful!\n"));
	} else
		return -EBUSY;
	/*This register is a 16-bit timer with a resolution of 1us. This is the
	timer used for interrupt delay/coalescing in the PCIe Application Layer.
	Zero is not a valid value. A value of 1 in the register will cause the
	interrupts to be normal. A value greater than 1 will cause coalescing
	delays.*/
	pm8001_cw32(pm8001_ha, 1, 0x0033c0, 0x1);
	pm8001_cw32(pm8001_ha, 1, 0x0033c4, 0x0);
	return 0;
}
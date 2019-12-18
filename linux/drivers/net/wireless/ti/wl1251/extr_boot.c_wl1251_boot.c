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
typedef  int u32 ;
struct TYPE_2__ {int radio_type; int major; int minor; } ;
struct wl1251 {int fw_len; TYPE_1__ boot_attr; scalar_t__ use_eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_EEPROMLESS_IND_REG ; 
 int /*<<< orphan*/  ACX_REG_ECPU_CONTROL ; 
 int /*<<< orphan*/  ACX_REG_EE_START ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int ECPU_CONTROL_HALT ; 
 int EIO ; 
 int /*<<< orphan*/  SCR_PAD2 ; 
 int /*<<< orphan*/  SCR_PAD3 ; 
 int START_EEPROM_MGR ; 
 int USE_EEPROM ; 
 int /*<<< orphan*/  msleep (int) ; 
 int wl1251_boot_init_seq (struct wl1251*) ; 
 int wl1251_boot_run_firmware (struct wl1251*) ; 
 int wl1251_boot_soft_reset (struct wl1251*) ; 
 int wl1251_boot_upload_firmware (struct wl1251*) ; 
 int wl1251_boot_upload_nvs (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int) ; 

int wl1251_boot(struct wl1251 *wl)
{
	int ret = 0, minor_minor_e2_ver;
	u32 tmp, boot_data;

	/* halt embedded ARM CPU while loading firmware */
	wl1251_reg_write32(wl, ACX_REG_ECPU_CONTROL, ECPU_CONTROL_HALT);

	ret = wl1251_boot_soft_reset(wl);
	if (ret < 0)
		goto out;

	/* 2. start processing NVS file */
	if (wl->use_eeprom) {
		wl1251_reg_write32(wl, ACX_REG_EE_START, START_EEPROM_MGR);
		/* Wait for EEPROM NVS burst read to complete */
		msleep(40);
		wl1251_reg_write32(wl, ACX_EEPROMLESS_IND_REG, USE_EEPROM);
	} else {
		ret = wl1251_boot_upload_nvs(wl);
		if (ret < 0)
			goto out;

		/* write firmware's last address (ie. it's length) to
		 * ACX_EEPROMLESS_IND_REG */
		wl1251_reg_write32(wl, ACX_EEPROMLESS_IND_REG, wl->fw_len);
	}

	/* 6. read the EEPROM parameters */
	tmp = wl1251_reg_read32(wl, SCR_PAD2);

	/* 7. read bootdata */
	wl->boot_attr.radio_type = (tmp & 0x0000FF00) >> 8;
	wl->boot_attr.major = (tmp & 0x00FF0000) >> 16;
	tmp = wl1251_reg_read32(wl, SCR_PAD3);

	/* 8. check bootdata and call restart sequence */
	wl->boot_attr.minor = (tmp & 0x00FF0000) >> 16;
	minor_minor_e2_ver = (tmp & 0xFF000000) >> 24;

	wl1251_debug(DEBUG_BOOT, "radioType 0x%x majorE2Ver 0x%x "
		     "minorE2Ver 0x%x minor_minor_e2_ver 0x%x",
		     wl->boot_attr.radio_type, wl->boot_attr.major,
		     wl->boot_attr.minor, minor_minor_e2_ver);

	ret = wl1251_boot_init_seq(wl);
	if (ret < 0)
		goto out;

	/* 9. NVS processing done */
	boot_data = wl1251_reg_read32(wl, ACX_REG_ECPU_CONTROL);

	wl1251_debug(DEBUG_BOOT, "halt boot_data 0x%x", boot_data);

	/* 10. check that ECPU_CONTROL_HALT bits are set in
	 * pWhalBus->uBootData and start uploading firmware
	 */
	if ((boot_data & ECPU_CONTROL_HALT) == 0) {
		wl1251_error("boot failed, ECPU_CONTROL_HALT not set");
		ret = -EIO;
		goto out;
	}

	ret = wl1251_boot_upload_firmware(wl);
	if (ret < 0)
		goto out;

	/* 10.5 start firmware */
	ret = wl1251_boot_run_firmware(wl);
	if (ret < 0)
		goto out;

out:
	return ret;
}
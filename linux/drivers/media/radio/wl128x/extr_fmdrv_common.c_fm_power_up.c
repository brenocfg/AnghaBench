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
typedef  int /*<<< orphan*/  u16 ;
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;
typedef  int /*<<< orphan*/  asic_ver ;
typedef  int /*<<< orphan*/  asic_id ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_ID_GET ; 
 int /*<<< orphan*/  ASIC_VER_GET ; 
 int EINVAL ; 
 int /*<<< orphan*/  FM_ENABLE ; 
 char* FM_FMC_FW_FILE_START ; 
 scalar_t__ FM_MODE_ENTRY_MAX ; 
 scalar_t__ FM_MODE_RX ; 
 int /*<<< orphan*/  FM_POWER_MODE ; 
 char* FM_RX_FW_FILE_START ; 
 char* FM_TX_FW_FILE_START ; 
 int /*<<< orphan*/  REG_RD ; 
 int /*<<< orphan*/  REG_WR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int fm_download_firmware (struct fmdev*,scalar_t__*) ; 
 int fmc_prepare (struct fmdev*) ; 
 int fmc_release (struct fmdev*) ; 
 scalar_t__ fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fmdbg (char*,...) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char*,int,int) ; 

__attribute__((used)) static int fm_power_up(struct fmdev *fmdev, u8 mode)
{
	u16 payload;
	__be16 asic_id = 0, asic_ver = 0;
	int resp_len, ret;
	u8 fw_name[50];

	if (mode >= FM_MODE_ENTRY_MAX) {
		fmerr("Invalid firmware download option\n");
		return -EINVAL;
	}

	/*
	 * Initialize FM common module. FM GPIO toggling is
	 * taken care in Shared Transport driver.
	 */
	ret = fmc_prepare(fmdev);
	if (ret < 0) {
		fmerr("Unable to prepare FM Common\n");
		return ret;
	}

	payload = FM_ENABLE;
	if (fmc_send_cmd(fmdev, FM_POWER_MODE, REG_WR, &payload,
			sizeof(payload), NULL, NULL))
		goto rel;

	/* Allow the chip to settle down in Channel-8 mode */
	msleep(20);

	if (fmc_send_cmd(fmdev, ASIC_ID_GET, REG_RD, NULL,
			sizeof(asic_id), &asic_id, &resp_len))
		goto rel;

	if (fmc_send_cmd(fmdev, ASIC_VER_GET, REG_RD, NULL,
			sizeof(asic_ver), &asic_ver, &resp_len))
		goto rel;

	fmdbg("ASIC ID: 0x%x , ASIC Version: %d\n",
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	sprintf(fw_name, "%s_%x.%d.bts", FM_FMC_FW_FILE_START,
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_download_firmware(fmdev, fw_name);
	if (ret < 0) {
		fmdbg("Failed to download firmware file %s\n", fw_name);
		goto rel;
	}
	sprintf(fw_name, "%s_%x.%d.bts", (mode == FM_MODE_RX) ?
			FM_RX_FW_FILE_START : FM_TX_FW_FILE_START,
			be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_download_firmware(fmdev, fw_name);
	if (ret < 0) {
		fmdbg("Failed to download firmware file %s\n", fw_name);
		goto rel;
	} else
		return ret;
rel:
	return fmc_release(fmdev);
}
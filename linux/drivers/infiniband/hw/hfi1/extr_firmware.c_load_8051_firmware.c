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
typedef  unsigned long long u64 ;
struct hfi1_devdata {int /*<<< orphan*/  dc8051_ver; } ;
struct firmware_details {int /*<<< orphan*/  signature; int /*<<< orphan*/  firmware_len; int /*<<< orphan*/  firmware_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_CFG_RST ; 
 unsigned long long DC_DC8051_CFG_RST_CRAM_SMASK ; 
 unsigned long long DC_DC8051_CFG_RST_DRAM_SMASK ; 
 unsigned long long DC_DC8051_CFG_RST_IRAM_SMASK ; 
 unsigned long long DC_DC8051_CFG_RST_M8051W_SMASK ; 
 unsigned long long DC_DC8051_CFG_RST_SFR_SMASK ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int HCMD_SUCCESS ; 
 int /*<<< orphan*/  HOST_INTERFACE_VERSION ; 
 int /*<<< orphan*/  MISC_CFG_FW_CTRL ; 
 unsigned long long MISC_CFG_FW_CTRL_FW_8051_LOADED_SMASK ; 
 int /*<<< orphan*/  TIMEOUT_8051_START ; 
 int /*<<< orphan*/  dc8051_ver (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int,int,int) ; 
 int get_firmware_state (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  load_security_variables (struct hfi1_devdata*,struct firmware_details*) ; 
 int /*<<< orphan*/  read_misc_status (struct hfi1_devdata*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int run_rsa (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int wait_fm_ready (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int write_8051 (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int write_host_interface_version (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_8051_firmware(struct hfi1_devdata *dd,
			      struct firmware_details *fdet)
{
	u64 reg;
	int ret;
	u8 ver_major;
	u8 ver_minor;
	u8 ver_patch;

	/*
	 * DC Reset sequence
	 * Load DC 8051 firmware
	 */
	/*
	 * DC reset step 1: Reset DC8051
	 */
	reg = DC_DC8051_CFG_RST_M8051W_SMASK
		| DC_DC8051_CFG_RST_CRAM_SMASK
		| DC_DC8051_CFG_RST_DRAM_SMASK
		| DC_DC8051_CFG_RST_IRAM_SMASK
		| DC_DC8051_CFG_RST_SFR_SMASK;
	write_csr(dd, DC_DC8051_CFG_RST, reg);

	/*
	 * DC reset step 2 (optional): Load 8051 data memory with link
	 * configuration
	 */

	/*
	 * DC reset step 3: Load DC8051 firmware
	 */
	/* release all but the core reset */
	reg = DC_DC8051_CFG_RST_M8051W_SMASK;
	write_csr(dd, DC_DC8051_CFG_RST, reg);

	/* Firmware load step 1 */
	load_security_variables(dd, fdet);

	/*
	 * Firmware load step 2.  Clear MISC_CFG_FW_CTRL.FW_8051_LOADED
	 */
	write_csr(dd, MISC_CFG_FW_CTRL, 0);

	/* Firmware load steps 3-5 */
	ret = write_8051(dd, 1/*code*/, 0, fdet->firmware_ptr,
			 fdet->firmware_len);
	if (ret)
		return ret;

	/*
	 * DC reset step 4. Host starts the DC8051 firmware
	 */
	/*
	 * Firmware load step 6.  Set MISC_CFG_FW_CTRL.FW_8051_LOADED
	 */
	write_csr(dd, MISC_CFG_FW_CTRL, MISC_CFG_FW_CTRL_FW_8051_LOADED_SMASK);

	/* Firmware load steps 7-10 */
	ret = run_rsa(dd, "8051", fdet->signature);
	if (ret)
		return ret;

	/* clear all reset bits, releasing the 8051 */
	write_csr(dd, DC_DC8051_CFG_RST, 0ull);

	/*
	 * DC reset step 5. Wait for firmware to be ready to accept host
	 * requests.
	 */
	ret = wait_fm_ready(dd, TIMEOUT_8051_START);
	if (ret) { /* timed out */
		dd_dev_err(dd, "8051 start timeout, current state 0x%x\n",
			   get_firmware_state(dd));
		return -ETIMEDOUT;
	}

	read_misc_status(dd, &ver_major, &ver_minor, &ver_patch);
	dd_dev_info(dd, "8051 firmware version %d.%d.%d\n",
		    (int)ver_major, (int)ver_minor, (int)ver_patch);
	dd->dc8051_ver = dc8051_ver(ver_major, ver_minor, ver_patch);
	ret = write_host_interface_version(dd, HOST_INTERFACE_VERSION);
	if (ret != HCMD_SUCCESS) {
		dd_dev_err(dd,
			   "Failed to set host interface version, return 0x%x\n",
			   ret);
		return -EIO;
	}

	return 0;
}
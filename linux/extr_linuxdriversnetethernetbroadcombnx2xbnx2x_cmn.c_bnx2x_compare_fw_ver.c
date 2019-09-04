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
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;
typedef  scalar_t__ BCM_5710_FW_MAJOR_VERSION ;

/* Variables and functions */
 int BCM_5710_FW_ENGINEERING_VERSION ; 
 int BCM_5710_FW_MINOR_VERSION ; 
 int BCM_5710_FW_REVISION_VERSION ; 
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int EBUSY ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON_CHIP ; 
 scalar_t__ REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSEM_REG_PRAM ; 

int bnx2x_compare_fw_ver(struct bnx2x *bp, u32 load_code, bool print_err)
{
	/* is another pf loaded on this engine? */
	if (load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP &&
	    load_code != FW_MSG_CODE_DRV_LOAD_COMMON) {
		/* build my FW version dword */
		u32 my_fw = (BCM_5710_FW_MAJOR_VERSION) +
			(BCM_5710_FW_MINOR_VERSION << 8) +
			(BCM_5710_FW_REVISION_VERSION << 16) +
			(BCM_5710_FW_ENGINEERING_VERSION << 24);

		/* read loaded FW from chip */
		u32 loaded_fw = REG_RD(bp, XSEM_REG_PRAM);

		DP(BNX2X_MSG_SP, "loaded fw %x, my fw %x\n",
		   loaded_fw, my_fw);

		/* abort nic load if version mismatch */
		if (my_fw != loaded_fw) {
			if (print_err)
				BNX2X_ERR("bnx2x with FW %x was already loaded which mismatches my %x FW. Aborting\n",
					  loaded_fw, my_fw);
			else
				BNX2X_DEV_INFO("bnx2x with FW %x was already loaded which mismatches my %x FW, possibly due to MF UNDI\n",
					       loaded_fw, my_fw);
			return -EBUSY;
		}
	}
	return 0;
}
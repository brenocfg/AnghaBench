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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  portvec; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_PHYFW ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Y_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Z_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T4_MEMORY_WRITE ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int t4_memory_rw (struct adapter*,int,unsigned long,unsigned long,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t4_phy_fw_ver (struct adapter*,int*) ; 
 int t4_query_params_rw (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*,int,int) ; 
 int t4_set_params_timeout (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*,int) ; 

int t4_load_phy_fw(struct adapter *adap,
		   int win, spinlock_t *win_lock,
		   int (*phy_fw_version)(const u8 *, size_t),
		   const u8 *phy_fw_data, size_t phy_fw_size)
{
	unsigned long mtype = 0, maddr = 0;
	u32 param, val;
	int cur_phy_fw_ver = 0, new_phy_fw_vers = 0;
	int ret;

	/* If we have version number support, then check to see if the adapter
	 * already has up-to-date PHY firmware loaded.
	 */
	if (phy_fw_version) {
		new_phy_fw_vers = phy_fw_version(phy_fw_data, phy_fw_size);
		ret = t4_phy_fw_ver(adap, &cur_phy_fw_ver);
		if (ret < 0)
			return ret;

		if (cur_phy_fw_ver >= new_phy_fw_vers) {
			CH_WARN(adap, "PHY Firmware already up-to-date, "
				"version %#x\n", cur_phy_fw_ver);
			return 0;
		}
	}

	/* Ask the firmware where it wants us to copy the PHY firmware image.
	 * The size of the file requires a special version of the READ command
	 * which will pass the file size via the values field in PARAMS_CMD and
	 * retrieve the return value from firmware and place it in the same
	 * buffer values
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PHYFW) |
		 FW_PARAMS_PARAM_Y_V(adap->params.portvec) |
		 FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD));
	val = phy_fw_size;
	ret = t4_query_params_rw(adap, adap->mbox, adap->pf, 0, 1,
				 &param, &val, 1, true);
	if (ret < 0)
		return ret;
	mtype = val >> 8;
	maddr = (val & 0xff) << 16;

	/* Copy the supplied PHY Firmware image to the adapter memory location
	 * allocated by the adapter firmware.
	 */
	if (win_lock)
		spin_lock_bh(win_lock);
	ret = t4_memory_rw(adap, win, mtype, maddr,
			   phy_fw_size, (__be32 *)phy_fw_data,
			   T4_MEMORY_WRITE);
	if (win_lock)
		spin_unlock_bh(win_lock);
	if (ret)
		return ret;

	/* Tell the firmware that the PHY firmware image has been written to
	 * RAM and it can now start copying it over to the PHYs.  The chip
	 * firmware will RESET the affected PHYs as part of this operation
	 * leaving them running the new PHY firmware image.
	 */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_PHYFW) |
		 FW_PARAMS_PARAM_Y_V(adap->params.portvec) |
		 FW_PARAMS_PARAM_Z_V(FW_PARAMS_PARAM_DEV_PHYFW_DOWNLOAD));
	ret = t4_set_params_timeout(adap, adap->mbox, adap->pf, 0, 1,
				    &param, &val, 30000);

	/* If we have version number support, then check to see that the new
	 * firmware got loaded properly.
	 */
	if (phy_fw_version) {
		ret = t4_phy_fw_ver(adap, &cur_phy_fw_ver);
		if (ret < 0)
			return ret;

		if (cur_phy_fw_ver != new_phy_fw_vers) {
			CH_WARN(adap, "PHY Firmware did not update: "
				"version on adapter %#x, "
				"version flashed %#x\n",
				cur_phy_fw_ver, new_phy_fw_vers);
			return -ENXIO;
		}
	}

	return 1;
}
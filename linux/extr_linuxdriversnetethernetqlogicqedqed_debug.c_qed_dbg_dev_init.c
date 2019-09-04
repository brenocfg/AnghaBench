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
typedef  int u8 ;
struct qed_ptt {int dummy; } ;
struct dbg_tools_data {int initialized; scalar_t__ chip_id; int* mode_enable; int num_ports; int use_dmae; int /*<<< orphan*/  num_pfs_per_port; int /*<<< orphan*/  platform_id; int /*<<< orphan*/  num_vfs; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 scalar_t__ CHIP_BB ; 
 scalar_t__ CHIP_K2 ; 
 int /*<<< orphan*/  CNIG_REG_NW_PORT_MODE_BB ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_UNKNOWN_CHIP ; 
 int MAX_NUM_PFS_BB ; 
 int MAX_NUM_PFS_K2 ; 
 int /*<<< orphan*/  MAX_NUM_VFS_BB ; 
 int /*<<< orphan*/  MAX_NUM_VFS_K2 ; 
 int /*<<< orphan*/  MISC_REG_PORT_MODE ; 
 size_t MODE_100G ; 
 size_t MODE_ASIC ; 
 size_t MODE_BB ; 
 size_t MODE_K2 ; 
 size_t MODE_PORTS_PER_ENG_1 ; 
 size_t MODE_PORTS_PER_ENG_2 ; 
 size_t MODE_PORTS_PER_ENG_4 ; 
 int /*<<< orphan*/  PLATFORM_ASIC ; 
 scalar_t__ QED_IS_BB_B0 (int /*<<< orphan*/ ) ; 
 scalar_t__ QED_IS_K2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qed_dbg_grc_init_params (struct qed_hwfn*) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static enum dbg_status qed_dbg_dev_init(struct qed_hwfn *p_hwfn,
					struct qed_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 num_pfs = 0, max_pfs_per_port = 0;

	if (dev_data->initialized)
		return DBG_STATUS_OK;

	/* Set chip */
	if (QED_IS_K2(p_hwfn->cdev)) {
		dev_data->chip_id = CHIP_K2;
		dev_data->mode_enable[MODE_K2] = 1;
		dev_data->num_vfs = MAX_NUM_VFS_K2;
		num_pfs = MAX_NUM_PFS_K2;
		max_pfs_per_port = MAX_NUM_PFS_K2 / 2;
	} else if (QED_IS_BB_B0(p_hwfn->cdev)) {
		dev_data->chip_id = CHIP_BB;
		dev_data->mode_enable[MODE_BB] = 1;
		dev_data->num_vfs = MAX_NUM_VFS_BB;
		num_pfs = MAX_NUM_PFS_BB;
		max_pfs_per_port = MAX_NUM_PFS_BB;
	} else {
		return DBG_STATUS_UNKNOWN_CHIP;
	}

	/* Set platofrm */
	dev_data->platform_id = PLATFORM_ASIC;
	dev_data->mode_enable[MODE_ASIC] = 1;

	/* Set port mode */
	switch (qed_rd(p_hwfn, p_ptt, MISC_REG_PORT_MODE)) {
	case 0:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_1] = 1;
		break;
	case 1:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_2] = 1;
		break;
	case 2:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_4] = 1;
		break;
	}

	/* Set 100G mode */
	if (dev_data->chip_id == CHIP_BB &&
	    qed_rd(p_hwfn, p_ptt, CNIG_REG_NW_PORT_MODE_BB) == 2)
		dev_data->mode_enable[MODE_100G] = 1;

	/* Set number of ports */
	if (dev_data->mode_enable[MODE_PORTS_PER_ENG_1] ||
	    dev_data->mode_enable[MODE_100G])
		dev_data->num_ports = 1;
	else if (dev_data->mode_enable[MODE_PORTS_PER_ENG_2])
		dev_data->num_ports = 2;
	else if (dev_data->mode_enable[MODE_PORTS_PER_ENG_4])
		dev_data->num_ports = 4;

	/* Set number of PFs per port */
	dev_data->num_pfs_per_port = min_t(u32,
					   num_pfs / dev_data->num_ports,
					   max_pfs_per_port);

	/* Initializes the GRC parameters */
	qed_dbg_grc_init_params(p_hwfn);

	dev_data->use_dmae = true;
	dev_data->initialized = 1;

	return DBG_STATUS_OK;
}
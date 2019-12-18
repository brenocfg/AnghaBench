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
typedef  int /*<<< orphan*/  uint8_t ;
struct fw_fcoe_port_stats {int dummy; } ;
struct fw_fcoe_port_cmd_params {int idx; int nstats; int /*<<< orphan*/  portid; } ;
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*) ; 
 int /*<<< orphan*/  csio_fcoe_read_portparams_init_mb (struct csio_hw*,struct csio_mb*,int /*<<< orphan*/ ,struct fw_fcoe_port_cmd_params*,int /*<<< orphan*/ *) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_mb_process_portparams_rsp (struct csio_hw*,struct csio_mb*,int*,struct fw_fcoe_port_cmd_params*,struct fw_fcoe_port_stats*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 

int
csio_get_phy_port_stats(struct csio_hw *hw, uint8_t portid,
			struct fw_fcoe_port_stats *port_stats)
{
	struct csio_mb  *mbp;
	struct fw_fcoe_port_cmd_params portparams;
	enum fw_retval retval;
	int idx;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		csio_err(hw, "FCoE FCF PARAMS command out of memory!\n");
		return -EINVAL;
	}
	portparams.portid = portid;

	for (idx = 1; idx <= 3; idx++) {
		portparams.idx = (idx-1)*6 + 1;
		portparams.nstats = 6;
		if (idx == 3)
			portparams.nstats = 4;
		csio_fcoe_read_portparams_init_mb(hw, mbp, CSIO_MB_DEFAULT_TMO,
							&portparams, NULL);
		if (csio_mb_issue(hw, mbp)) {
			csio_err(hw, "Issue of FCoE port params failed!\n");
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}
		csio_mb_process_portparams_rsp(hw, mbp, &retval,
						&portparams, port_stats);
	}

	mempool_free(mbp, hw->mb_mempool);
	return 0;
}
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
typedef  scalar_t__ uint8_t ;
struct fw_fcoe_link_cmd {int /*<<< orphan*/  phy_mac; int /*<<< orphan*/  vnport_wwpn; int /*<<< orphan*/  vnport_wwnn; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_lnode {scalar_t__ portid; struct csio_hw* hwp; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; TYPE_1__* pport; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
struct TYPE_2__ {scalar_t__ portid; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int CSIO_MAX_PPORTS ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FCOE_LINK_DOWN ; 
 scalar_t__ FCOE_LINK_UP ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,char*,...) ; 
 int /*<<< orphan*/  csio_ln_wwnn (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_ln_wwpn (struct csio_lnode*) ; 
 int csio_mb_fw_retval (struct csio_mb*) ; 
 scalar_t__ csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 int /*<<< orphan*/  csio_write_fcoe_link_cond_init_mb (struct csio_lnode*,struct csio_mb*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_err_nomem ; 

__attribute__((used)) static int
csio_fcoe_enable_link(struct csio_lnode *ln, bool enable)
{
	struct csio_hw *hw = ln->hwp;
	struct csio_mb  *mbp;
	enum fw_retval retval;
	uint8_t portid;
	uint8_t sub_op;
	struct fw_fcoe_link_cmd *lcmd;
	int i;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		return -ENOMEM;
	}

	portid = ln->portid;
	sub_op = enable ? FCOE_LINK_UP : FCOE_LINK_DOWN;

	csio_dbg(hw, "bringing FCOE LINK %s on Port:%d\n",
		 sub_op ? "UP" : "DOWN", portid);

	csio_write_fcoe_link_cond_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
					  portid, sub_op, 0, 0, 0, NULL);

	if (csio_mb_issue(hw, mbp)) {
		csio_err(hw, "failed to issue FCOE LINK cmd on port[%d]\n",
			portid);
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	retval = csio_mb_fw_retval(mbp);
	if (retval != FW_SUCCESS) {
		csio_err(hw,
			 "FCOE LINK %s cmd on port[%d] failed with "
			 "ret:x%x\n", sub_op ? "UP" : "DOWN", portid, retval);
		mempool_free(mbp, hw->mb_mempool);
		return -EINVAL;
	}

	if (!enable)
		goto out;

	lcmd = (struct fw_fcoe_link_cmd *)mbp->mb;

	memcpy(csio_ln_wwnn(ln), lcmd->vnport_wwnn, 8);
	memcpy(csio_ln_wwpn(ln), lcmd->vnport_wwpn, 8);

	for (i = 0; i < CSIO_MAX_PPORTS; i++)
		if (hw->pport[i].portid == portid)
			memcpy(hw->pport[i].mac, lcmd->phy_mac, 6);

out:
	mempool_free(mbp, hw->mb_mempool);
	return 0;
}
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
struct fw_fcoe_vnp_cmd {int /*<<< orphan*/  alloc_to_len16; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_lnode {int /*<<< orphan*/  vnp_flowid; int /*<<< orphan*/  fcf_flowid; } ;
struct csio_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  mb_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_MB_DEFAULT_TMO ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FW_CMD_RETVAL_G (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_SUCCESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  csio_fcoe_vnp_free_init_mb (struct csio_lnode*,struct csio_mb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*,...) ; 
 int csio_mb_issue (struct csio_hw*,struct csio_mb*) ; 
 struct csio_mb* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  n_err_nomem ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csio_fcoe_free_vnp(struct csio_hw *hw, struct csio_lnode *ln)
{
	struct csio_mb  *mbp;
	struct fw_fcoe_vnp_cmd *rsp;
	int ret = 0;
	int retry = 0;

	/* Issue VNP cmd to free vport */
	/* Allocate Mbox request */

	spin_lock_irq(&hw->lock);
	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_err_nomem);
		ret = -ENOMEM;
		goto out;
	}

	csio_fcoe_vnp_free_init_mb(ln, mbp, CSIO_MB_DEFAULT_TMO,
				   ln->fcf_flowid, ln->vnp_flowid,
				   NULL);

	for (retry = 0; retry < 3; retry++) {
		ret = csio_mb_issue(hw, mbp);
		if (ret != -EBUSY)
			break;

		/* Retry if mbox returns busy */
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	}

	if (ret) {
		csio_ln_err(ln, "Failed to issue mbox FCoE VNP command\n");
		goto out_free;
	}

	/* Process Mbox response of VNP command */
	rsp = (struct fw_fcoe_vnp_cmd *)(mbp->mb);
	if (FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)) != FW_SUCCESS) {
		csio_ln_err(ln, "FCOE VNP FREE cmd returned 0x%x!\n",
			    FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16)));
		ret = -EINVAL;
	}

out_free:
	mempool_free(mbp, hw->mb_mempool);
out:
	spin_unlock_irq(&hw->lock);
	return ret;
}
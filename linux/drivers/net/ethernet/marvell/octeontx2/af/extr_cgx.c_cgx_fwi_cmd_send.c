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
typedef  int /*<<< orphan*/  u64 ;
struct lmac {int cmd_pend; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  resp; int /*<<< orphan*/  lmac_id; int /*<<< orphan*/  wq_cmd_cmplt; struct cgx* cgx; } ;
struct device {int dummy; } ;
struct cgx {int /*<<< orphan*/  cgx_id; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGX_CMD_OWN_FIRMWARE ; 
 scalar_t__ CGX_CMD_OWN_NS ; 
 int /*<<< orphan*/  CGX_CMD_TIMEOUT ; 
 int /*<<< orphan*/  CGX_COMMAND_REG ; 
 int /*<<< orphan*/  CMDREG_OWN ; 
 int EBUSY ; 
 int EIO ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgx_read (struct cgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgx_write (struct cgx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgx_fwi_cmd_send(u64 req, u64 *resp, struct lmac *lmac)
{
	struct cgx *cgx = lmac->cgx;
	struct device *dev;
	int err = 0;
	u64 cmd;

	/* Ensure no other command is in progress */
	err = mutex_lock_interruptible(&lmac->cmd_lock);
	if (err)
		return err;

	/* Ensure command register is free */
	cmd = cgx_read(cgx, lmac->lmac_id,  CGX_COMMAND_REG);
	if (FIELD_GET(CMDREG_OWN, cmd) != CGX_CMD_OWN_NS) {
		err = -EBUSY;
		goto unlock;
	}

	/* Update ownership in command request */
	req = FIELD_SET(CMDREG_OWN, CGX_CMD_OWN_FIRMWARE, req);

	/* Mark this lmac as pending, before we start */
	lmac->cmd_pend = true;

	/* Start command in hardware */
	cgx_write(cgx, lmac->lmac_id, CGX_COMMAND_REG, req);

	/* Ensure command is completed without errors */
	if (!wait_event_timeout(lmac->wq_cmd_cmplt, !lmac->cmd_pend,
				msecs_to_jiffies(CGX_CMD_TIMEOUT))) {
		dev = &cgx->pdev->dev;
		dev_err(dev, "cgx port %d:%d cmd timeout\n",
			cgx->cgx_id, lmac->lmac_id);
		err = -EIO;
		goto unlock;
	}

	/* we have a valid command response */
	smp_rmb(); /* Ensure the latest updates are visible */
	*resp = lmac->resp;

unlock:
	mutex_unlock(&lmac->cmd_lock);

	return err;
}
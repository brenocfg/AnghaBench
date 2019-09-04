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
typedef  int u32 ;
struct dmae_command {int dummy; } ;
struct bnx2x {scalar_t__ recovery_state; int /*<<< orphan*/  dmae_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_DMAE ; 
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 scalar_t__ BNX2X_RECOVERY_NIC_LOADING ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int DMAE_COMP_VAL ; 
 int DMAE_PCI_ERROR ; 
 int DMAE_PCI_ERR_FLAG ; 
 int DMAE_TIMEOUT ; 
 int /*<<< orphan*/  INIT_DMAE_C (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dp_dmae (struct bnx2x*,struct dmae_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_post_dmae (struct bnx2x*,struct dmae_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int bnx2x_issue_dmae_with_comp(struct bnx2x *bp, struct dmae_command *dmae,
			       u32 *comp)
{
	int cnt = CHIP_REV_IS_SLOW(bp) ? (400000) : 4000;
	int rc = 0;

	bnx2x_dp_dmae(bp, dmae, BNX2X_MSG_DMAE);

	/* Lock the dmae channel. Disable BHs to prevent a dead-lock
	 * as long as this code is called both from syscall context and
	 * from ndo_set_rx_mode() flow that may be called from BH.
	 */

	spin_lock_bh(&bp->dmae_lock);

	/* reset completion */
	*comp = 0;

	/* post the command on the channel used for initializations */
	bnx2x_post_dmae(bp, dmae, INIT_DMAE_C(bp));

	/* wait for completion */
	udelay(5);
	while ((*comp & ~DMAE_PCI_ERR_FLAG) != DMAE_COMP_VAL) {

		if (!cnt ||
		    (bp->recovery_state != BNX2X_RECOVERY_DONE &&
		     bp->recovery_state != BNX2X_RECOVERY_NIC_LOADING)) {
			BNX2X_ERR("DMAE timeout!\n");
			rc = DMAE_TIMEOUT;
			goto unlock;
		}
		cnt--;
		udelay(50);
	}
	if (*comp & DMAE_PCI_ERR_FLAG) {
		BNX2X_ERR("DMAE PCI error!\n");
		rc = DMAE_PCI_ERROR;
	}

unlock:

	spin_unlock_bh(&bp->dmae_lock);

	return rc;
}
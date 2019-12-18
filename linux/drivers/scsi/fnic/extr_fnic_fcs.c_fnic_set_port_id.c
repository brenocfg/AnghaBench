#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * ctl_src_addr; } ;
struct fnic {scalar_t__ state; int /*<<< orphan*/  fnic_lock; TYPE_1__* lport; TYPE_3__ ctlr; } ;
struct fc_lport {int /*<<< orphan*/  host; } ;
struct fc_frame {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * granted_mac; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_FCS_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ FNIC_IN_ETH_MODE ; 
 scalar_t__ FNIC_IN_ETH_TRANS_FC_MODE ; 
 scalar_t__ FNIC_IN_FC_MODE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  fcoe_ctlr_recv_flogi (TYPE_3__*,struct fc_lport*,struct fc_frame*) ; 
 int fnic_flogi_reg_handler (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnic_set_eth_mode (struct fnic*) ; 
 int /*<<< orphan*/  fnic_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  fnic_update_mac (struct fc_lport*,int /*<<< orphan*/ *) ; 
 TYPE_2__* fr_cb (struct fc_frame*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void fnic_set_port_id(struct fc_lport *lport, u32 port_id, struct fc_frame *fp)
{
	struct fnic *fnic = lport_priv(lport);
	u8 *mac;
	int ret;

	FNIC_FCS_DBG(KERN_DEBUG, lport->host, "set port_id %x fp %p\n",
		     port_id, fp);

	/*
	 * If we're clearing the FC_ID, change to use the ctl_src_addr.
	 * Set ethernet mode to send FLOGI.
	 */
	if (!port_id) {
		fnic_update_mac(lport, fnic->ctlr.ctl_src_addr);
		fnic_set_eth_mode(fnic);
		return;
	}

	if (fp) {
		mac = fr_cb(fp)->granted_mac;
		if (is_zero_ether_addr(mac)) {
			/* non-FIP - FLOGI already accepted - ignore return */
			fcoe_ctlr_recv_flogi(&fnic->ctlr, lport, fp);
		}
		fnic_update_mac(lport, mac);
	}

	/* Change state to reflect transition to FC mode */
	spin_lock_irq(&fnic->fnic_lock);
	if (fnic->state == FNIC_IN_ETH_MODE || fnic->state == FNIC_IN_FC_MODE)
		fnic->state = FNIC_IN_ETH_TRANS_FC_MODE;
	else {
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			     "Unexpected fnic state %s while"
			     " processing flogi resp\n",
			     fnic_state_to_str(fnic->state));
		spin_unlock_irq(&fnic->fnic_lock);
		return;
	}
	spin_unlock_irq(&fnic->fnic_lock);

	/*
	 * Send FLOGI registration to firmware to set up FC mode.
	 * The new address will be set up when registration completes.
	 */
	ret = fnic_flogi_reg_handler(fnic, port_id);

	if (ret < 0) {
		spin_lock_irq(&fnic->fnic_lock);
		if (fnic->state == FNIC_IN_ETH_TRANS_FC_MODE)
			fnic->state = FNIC_IN_ETH_MODE;
		spin_unlock_irq(&fnic->fnic_lock);
	}
}
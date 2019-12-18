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
typedef  int /*<<< orphan*/  u16 ;
struct timer_list {int dummy; } ;
struct cas {scalar_t__ link_transition_jiffies; int cas_flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  link_timer; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  reset_task_pending; int /*<<< orphan*/  reset_task_pending_all; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/  phy_type; int /*<<< orphan*/ * rx_last; int /*<<< orphan*/  reset_task_pending_mtu; int /*<<< orphan*/  reset_task_pending_spare; int /*<<< orphan*/  hw_running; scalar_t__ link_transition_jiffies_valid; } ;

/* Variables and functions */
 int CAS_FLAG_RXD_POST (int) ; 
 int CAS_FLAG_RXD_POST_MASK ; 
 scalar_t__ CAS_LINK_TIMEOUT ; 
 scalar_t__ CAS_PHY_MII (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_RESET_ALL ; 
 int CAS_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MAC_SM_ENCAP_SM ; 
 int /*<<< orphan*/  MAC_SM_TLM ; 
 int MAC_TX_FRAME_XMIT ; 
 int MAX_RX_DESC_RINGS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 scalar_t__ REG_MAC_STATE_MACHINE ; 
 scalar_t__ REG_MAC_TX_STATUS ; 
 scalar_t__ REG_MIF_STATUS ; 
 scalar_t__ REG_TX_FIFO_PKT_CNT ; 
 scalar_t__ REG_TX_FIFO_READ_PTR ; 
 scalar_t__ REG_TX_FIFO_WRITE_PTR ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_entropy_gather (struct cas*) ; 
 int /*<<< orphan*/  cas_hard_reset (struct cas*) ; 
 int /*<<< orphan*/  cas_lock_tx (struct cas*) ; 
 int /*<<< orphan*/  cas_mif_poll (struct cas*,int) ; 
 int cas_mii_link_check (struct cas*,int /*<<< orphan*/ ) ; 
 int cas_pcs_link_check (struct cas*) ; 
 int /*<<< orphan*/  cas_phy_read (struct cas*,int /*<<< orphan*/ ) ; 
 scalar_t__ cas_post_rxds_ringN (struct cas*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_unlock_tx (struct cas*) ; 
 struct cas* cp ; 
 struct cas* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  link_timer ; 
 scalar_t__ link_transition_timeout ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void cas_link_timer(struct timer_list *t)
{
	struct cas *cp = from_timer(cp, t, link_timer);
	int mask, pending = 0, reset = 0;
	unsigned long flags;

	if (link_transition_timeout != 0 &&
	    cp->link_transition_jiffies_valid &&
	    ((jiffies - cp->link_transition_jiffies) >
	      (link_transition_timeout))) {
		/* One-second counter so link-down workaround doesn't
		 * cause resets to occur so fast as to fool the switch
		 * into thinking the link is down.
		 */
		cp->link_transition_jiffies_valid = 0;
	}

	if (!cp->hw_running)
		return;

	spin_lock_irqsave(&cp->lock, flags);
	cas_lock_tx(cp);
	cas_entropy_gather(cp);

	/* If the link task is still pending, we just
	 * reschedule the link timer
	 */
#if 1
	if (atomic_read(&cp->reset_task_pending_all) ||
	    atomic_read(&cp->reset_task_pending_spare) ||
	    atomic_read(&cp->reset_task_pending_mtu))
		goto done;
#else
	if (atomic_read(&cp->reset_task_pending))
		goto done;
#endif

	/* check for rx cleaning */
	if ((mask = (cp->cas_flags & CAS_FLAG_RXD_POST_MASK))) {
		int i, rmask;

		for (i = 0; i < MAX_RX_DESC_RINGS; i++) {
			rmask = CAS_FLAG_RXD_POST(i);
			if ((mask & rmask) == 0)
				continue;

			/* post_rxds will do a mod_timer */
			if (cas_post_rxds_ringN(cp, i, cp->rx_last[i]) < 0) {
				pending = 1;
				continue;
			}
			cp->cas_flags &= ~rmask;
		}
	}

	if (CAS_PHY_MII(cp->phy_type)) {
		u16 bmsr;
		cas_mif_poll(cp, 0);
		bmsr = cas_phy_read(cp, MII_BMSR);
		/* WTZ: Solaris driver reads this twice, but that
		 * may be due to the PCS case and the use of a
		 * common implementation. Read it twice here to be
		 * safe.
		 */
		bmsr = cas_phy_read(cp, MII_BMSR);
		cas_mif_poll(cp, 1);
		readl(cp->regs + REG_MIF_STATUS); /* avoid dups */
		reset = cas_mii_link_check(cp, bmsr);
	} else {
		reset = cas_pcs_link_check(cp);
	}

	if (reset)
		goto done;

	/* check for tx state machine confusion */
	if ((readl(cp->regs + REG_MAC_TX_STATUS) & MAC_TX_FRAME_XMIT) == 0) {
		u32 val = readl(cp->regs + REG_MAC_STATE_MACHINE);
		u32 wptr, rptr;
		int tlm  = CAS_VAL(MAC_SM_TLM, val);

		if (((tlm == 0x5) || (tlm == 0x3)) &&
		    (CAS_VAL(MAC_SM_ENCAP_SM, val) == 0)) {
			netif_printk(cp, tx_err, KERN_DEBUG, cp->dev,
				     "tx err: MAC_STATE[%08x]\n", val);
			reset = 1;
			goto done;
		}

		val  = readl(cp->regs + REG_TX_FIFO_PKT_CNT);
		wptr = readl(cp->regs + REG_TX_FIFO_WRITE_PTR);
		rptr = readl(cp->regs + REG_TX_FIFO_READ_PTR);
		if ((val == 0) && (wptr != rptr)) {
			netif_printk(cp, tx_err, KERN_DEBUG, cp->dev,
				     "tx err: TX_FIFO[%08x:%08x:%08x]\n",
				     val, wptr, rptr);
			reset = 1;
		}

		if (reset)
			cas_hard_reset(cp);
	}

done:
	if (reset) {
#if 1
		atomic_inc(&cp->reset_task_pending);
		atomic_inc(&cp->reset_task_pending_all);
		schedule_work(&cp->reset_task);
#else
		atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
		pr_err("reset called in cas_link_timer\n");
		schedule_work(&cp->reset_task);
#endif
	}

	if (!pending)
		mod_timer(&cp->link_timer, jiffies + CAS_LINK_TIMEOUT);
	cas_unlock_tx(cp);
	spin_unlock_irqrestore(&cp->lock, flags);
}
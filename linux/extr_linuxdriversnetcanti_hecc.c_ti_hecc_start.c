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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ti_hecc_priv {TYPE_1__ can; scalar_t__ use_hecc1int; int /*<<< orphan*/  rx_next; int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  HECC_CANGAM ; 
 int /*<<< orphan*/  HECC_CANGIM ; 
 int HECC_CANGIM_DEF_MASK ; 
 int HECC_CANGIM_I0EN ; 
 int HECC_CANGIM_I1EN ; 
 int HECC_CANGIM_SIL ; 
 int /*<<< orphan*/  HECC_CANMD ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANMID ; 
 int /*<<< orphan*/  HECC_CANMID_AME ; 
 int /*<<< orphan*/  HECC_CANMIL ; 
 int /*<<< orphan*/  HECC_CANMIM ; 
 int /*<<< orphan*/  HECC_CANOPC ; 
 int HECC_MAX_MAILBOXES ; 
 scalar_t__ HECC_MAX_RX_MBOX ; 
 int /*<<< orphan*/  HECC_RX_FIRST_MBOX ; 
 int HECC_SET_REG ; 
 int /*<<< orphan*/  HECC_TX_MASK ; 
 int /*<<< orphan*/  hecc_clear_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hecc_set_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hecc_write_lam (struct ti_hecc_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  hecc_write_mbx (struct ti_hecc_priv*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ti_hecc_reset (struct net_device*) ; 

__attribute__((used)) static void ti_hecc_start(struct net_device *ndev)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	u32 cnt, mbxno, mbx_mask;

	/* put HECC in initialization mode and set btc */
	ti_hecc_reset(ndev);

	priv->tx_head = priv->tx_tail = HECC_TX_MASK;
	priv->rx_next = HECC_RX_FIRST_MBOX;

	/* Enable local and global acceptance mask registers */
	hecc_write(priv, HECC_CANGAM, HECC_SET_REG);

	/* Prepare configured mailboxes to receive messages */
	for (cnt = 0; cnt < HECC_MAX_RX_MBOX; cnt++) {
		mbxno = HECC_MAX_MAILBOXES - 1 - cnt;
		mbx_mask = BIT(mbxno);
		hecc_clear_bit(priv, HECC_CANME, mbx_mask);
		hecc_write_mbx(priv, mbxno, HECC_CANMID, HECC_CANMID_AME);
		hecc_write_lam(priv, mbxno, HECC_SET_REG);
		hecc_set_bit(priv, HECC_CANMD, mbx_mask);
		hecc_set_bit(priv, HECC_CANME, mbx_mask);
		hecc_set_bit(priv, HECC_CANMIM, mbx_mask);
	}

	/* Prevent message over-write & Enable interrupts */
	hecc_write(priv, HECC_CANOPC, HECC_SET_REG);
	if (priv->use_hecc1int) {
		hecc_write(priv, HECC_CANMIL, HECC_SET_REG);
		hecc_write(priv, HECC_CANGIM, HECC_CANGIM_DEF_MASK |
			HECC_CANGIM_I1EN | HECC_CANGIM_SIL);
	} else {
		hecc_write(priv, HECC_CANMIL, 0);
		hecc_write(priv, HECC_CANGIM,
			HECC_CANGIM_DEF_MASK | HECC_CANGIM_I0EN);
	}
	priv->can.state = CAN_STATE_ERROR_ACTIVE;
}
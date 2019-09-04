#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ks_net {TYPE_2__* netdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  rx_over_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IRQ_LCI ; 
 int IRQ_LDI ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IRQ_RXI ; 
 int IRQ_RXOI ; 
 int IRQ_TXI ; 
 int /*<<< orphan*/  KS_ISR ; 
 int /*<<< orphan*/  KS_PMECR ; 
 int PMECR_WKEVT_LINK ; 
 int PMECR_WKEVT_MASK ; 
 int /*<<< orphan*/  ks_rcv (struct ks_net*,struct net_device*) ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_restore_cmd_reg (struct ks_net*) ; 
 int /*<<< orphan*/  ks_save_cmd_reg (struct ks_net*) ; 
 int /*<<< orphan*/  ks_update_link_status (struct net_device*,struct ks_net*) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 struct ks_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ks_irq(int irq, void *pw)
{
	struct net_device *netdev = pw;
	struct ks_net *ks = netdev_priv(netdev);
	u16 status;

	/*this should be the first in IRQ handler */
	ks_save_cmd_reg(ks);

	status = ks_rdreg16(ks, KS_ISR);
	if (unlikely(!status)) {
		ks_restore_cmd_reg(ks);
		return IRQ_NONE;
	}

	ks_wrreg16(ks, KS_ISR, status);

	if (likely(status & IRQ_RXI))
		ks_rcv(ks, netdev);

	if (unlikely(status & IRQ_LCI))
		ks_update_link_status(netdev, ks);

	if (unlikely(status & IRQ_TXI))
		netif_wake_queue(netdev);

	if (unlikely(status & IRQ_LDI)) {

		u16 pmecr = ks_rdreg16(ks, KS_PMECR);
		pmecr &= ~PMECR_WKEVT_MASK;
		ks_wrreg16(ks, KS_PMECR, pmecr | PMECR_WKEVT_LINK);
	}

	if (unlikely(status & IRQ_RXOI))
		ks->netdev->stats.rx_over_errors++;
	/* this should be the last in IRQ handler*/
	ks_restore_cmd_reg(ks);
	return IRQ_HANDLED;
}
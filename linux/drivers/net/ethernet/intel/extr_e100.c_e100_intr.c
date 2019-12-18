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
typedef  int u8 ;
struct nic {int /*<<< orphan*/  napi; int /*<<< orphan*/  ru_running; TYPE_2__* csr; int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  stat_ack; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  RU_SUSPENDED ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e100_disable_irq (struct nic*) ; 
 int /*<<< orphan*/  intr ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int stat_ack_not_ours ; 
 int stat_ack_not_present ; 
 int stat_ack_rnr ; 

__attribute__((used)) static irqreturn_t e100_intr(int irq, void *dev_id)
{
	struct net_device *netdev = dev_id;
	struct nic *nic = netdev_priv(netdev);
	u8 stat_ack = ioread8(&nic->csr->scb.stat_ack);

	netif_printk(nic, intr, KERN_DEBUG, nic->netdev,
		     "stat_ack = 0x%02X\n", stat_ack);

	if (stat_ack == stat_ack_not_ours ||	/* Not our interrupt */
	   stat_ack == stat_ack_not_present)	/* Hardware is ejected */
		return IRQ_NONE;

	/* Ack interrupt(s) */
	iowrite8(stat_ack, &nic->csr->scb.stat_ack);

	/* We hit Receive No Resource (RNR); restart RU after cleaning */
	if (stat_ack & stat_ack_rnr)
		nic->ru_running = RU_SUSPENDED;

	if (likely(napi_schedule_prep(&nic->napi))) {
		e100_disable_irq(nic);
		__napi_schedule(&nic->napi);
	}

	return IRQ_HANDLED;
}
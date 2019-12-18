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
struct TYPE_2__ {int /*<<< orphan*/  sysctl_bar; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; int /*<<< orphan*/  txqueue_wake; } ;
struct qtnf_bus {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOPAZ_IPC_IRQ_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_LH_IPC4_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_RC_TX_STOP_IRQ ; 
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtnf_try_wake_xmit(struct qtnf_bus *bus, struct net_device *ndev)
{
	struct qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	int ready;

	ready = readl(ts->txqueue_wake);
	if (ready) {
		netif_wake_queue(ndev);
	} else {
		/* re-send irq to card: tx stopped */
		writel(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_STOP_IRQ),
		       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));
	}
}
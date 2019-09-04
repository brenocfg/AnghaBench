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
struct net_device {char* name; } ;
struct bnxt {int tx_nr_rings_per_tc; int cp_nr_rings; int flags; int rx_nr_rings; TYPE_1__* irq_tbl; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BNXT_FLAG_SHARED_RINGS ; 
 int bnxt_cp_num_to_irq_num (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_msix ; 
 int netdev_get_num_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int const,char*,char*,char*,int) ; 

__attribute__((used)) static void bnxt_setup_msix(struct bnxt *bp)
{
	const int len = sizeof(bp->irq_tbl[0].name);
	struct net_device *dev = bp->dev;
	int tcs, i;

	tcs = netdev_get_num_tc(dev);
	if (tcs > 1) {
		int i, off, count;

		for (i = 0; i < tcs; i++) {
			count = bp->tx_nr_rings_per_tc;
			off = i * count;
			netdev_set_tc_queue(dev, i, count, off);
		}
	}

	for (i = 0; i < bp->cp_nr_rings; i++) {
		int map_idx = bnxt_cp_num_to_irq_num(bp, i);
		char *attr;

		if (bp->flags & BNXT_FLAG_SHARED_RINGS)
			attr = "TxRx";
		else if (i < bp->rx_nr_rings)
			attr = "rx";
		else
			attr = "tx";

		snprintf(bp->irq_tbl[map_idx].name, len, "%s-%s-%d", dev->name,
			 attr, i);
		bp->irq_tbl[map_idx].handler = bnxt_msix;
	}
}
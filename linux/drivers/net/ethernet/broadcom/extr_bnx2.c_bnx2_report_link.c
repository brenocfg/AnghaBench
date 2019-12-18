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
struct bnx2 {scalar_t__ duplex; int flow_ctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  line_speed; scalar_t__ link_up; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  bnx2_report_fw_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_xceiver_str (struct bnx2*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void
bnx2_report_link(struct bnx2 *bp)
{
	if (bp->link_up) {
		netif_carrier_on(bp->dev);
		netdev_info(bp->dev, "NIC %s Link is Up, %d Mbps %s duplex",
			    bnx2_xceiver_str(bp),
			    bp->line_speed,
			    bp->duplex == DUPLEX_FULL ? "full" : "half");

		if (bp->flow_ctrl) {
			if (bp->flow_ctrl & FLOW_CTRL_RX) {
				pr_cont(", receive ");
				if (bp->flow_ctrl & FLOW_CTRL_TX)
					pr_cont("& transmit ");
			}
			else {
				pr_cont(", transmit ");
			}
			pr_cont("flow control ON");
		}
		pr_cont("\n");
	} else {
		netif_carrier_off(bp->dev);
		netdev_err(bp->dev, "NIC %s Link is Down\n",
			   bnx2_xceiver_str(bp));
	}

	bnx2_report_fw_link(bp);
}
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
struct myri10ge_priv {unsigned int link_state; void* rdma_tags_available; int /*<<< orphan*/  down_wq; int /*<<< orphan*/  down_cnt; int /*<<< orphan*/  dev; int /*<<< orphan*/  link_changes; TYPE_1__* ss; } ;
struct mcp_irq_data {scalar_t__ link_down; int /*<<< orphan*/  rdma_tags_available; int /*<<< orphan*/  link_up; int /*<<< orphan*/  stats_updated; } ;
struct TYPE_2__ {struct mcp_irq_data* fw_stats; } ;

/* Variables and functions */
 unsigned int MXGEFW_LINK_MYRINET ; 
 unsigned int MXGEFW_LINK_UP ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct myri10ge_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void myri10ge_check_statblock(struct myri10ge_priv *mgp)
{
	struct mcp_irq_data *stats = mgp->ss[0].fw_stats;

	if (unlikely(stats->stats_updated)) {
		unsigned link_up = ntohl(stats->link_up);
		if (mgp->link_state != link_up) {
			mgp->link_state = link_up;

			if (mgp->link_state == MXGEFW_LINK_UP) {
				netif_info(mgp, link, mgp->dev, "link up\n");
				netif_carrier_on(mgp->dev);
				mgp->link_changes++;
			} else {
				netif_info(mgp, link, mgp->dev, "link %s\n",
					   (link_up == MXGEFW_LINK_MYRINET ?
					    "mismatch (Myrinet detected)" :
					    "down"));
				netif_carrier_off(mgp->dev);
				mgp->link_changes++;
			}
		}
		if (mgp->rdma_tags_available !=
		    ntohl(stats->rdma_tags_available)) {
			mgp->rdma_tags_available =
			    ntohl(stats->rdma_tags_available);
			netdev_warn(mgp->dev, "RDMA timed out! %d tags left\n",
				    mgp->rdma_tags_available);
		}
		mgp->down_cnt += stats->link_down;
		if (stats->link_down)
			wake_up(&mgp->down_wq);
	}
}
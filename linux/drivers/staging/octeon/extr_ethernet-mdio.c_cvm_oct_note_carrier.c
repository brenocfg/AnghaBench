#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {int /*<<< orphan*/  netdev; int /*<<< orphan*/  queue; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {scalar_t__ full_duplex; int /*<<< orphan*/  speed; scalar_t__ link_up; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice_ratelimited (char*,int /*<<< orphan*/ ,...) ; 

void cvm_oct_note_carrier(struct octeon_ethernet *priv,
			  cvmx_helper_link_info_t li)
{
	if (li.s.link_up) {
		pr_notice_ratelimited("%s: %u Mbps %s duplex, port %d, queue %d\n",
				      netdev_name(priv->netdev), li.s.speed,
				      (li.s.full_duplex) ? "Full" : "Half",
				      priv->port, priv->queue);
	} else {
		pr_notice_ratelimited("%s: Link down\n",
				      netdev_name(priv->netdev));
	}
}
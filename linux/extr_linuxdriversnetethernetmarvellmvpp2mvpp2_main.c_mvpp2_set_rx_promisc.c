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
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; TYPE_1__* dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_PRS_L2_MULTI_CAST ; 
 int /*<<< orphan*/  MVPP2_PRS_L2_UNI_CAST ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  mvpp2_prs_mac_promisc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_prs_vid_disable_filtering (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_prs_vid_enable_filtering (struct mvpp2_port*) ; 

__attribute__((used)) static void mvpp2_set_rx_promisc(struct mvpp2_port *port, bool enable)
{
	if (!enable && (port->dev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		mvpp2_prs_vid_enable_filtering(port);
	else
		mvpp2_prs_vid_disable_filtering(port);

	mvpp2_prs_mac_promisc_set(port->priv, port->id,
				  MVPP2_PRS_L2_UNI_CAST, enable);

	mvpp2_prs_mac_promisc_set(port->priv, port->id,
				  MVPP2_PRS_L2_MULTI_CAST, enable);
}
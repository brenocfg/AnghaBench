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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long* advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys2ethtool_adver_link (unsigned long*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void get_advertising(u32 eth_proto_cap, u8 tx_pause, u8 rx_pause,
			    struct ethtool_link_ksettings *link_ksettings,
			    bool ext)
{
	unsigned long *advertising = link_ksettings->link_modes.advertising;
	ptys2ethtool_adver_link(advertising, eth_proto_cap, ext);

	if (rx_pause)
		ethtool_link_ksettings_add_link_mode(link_ksettings, advertising, Pause);
	if (tx_pause ^ rx_pause)
		ethtool_link_ksettings_add_link_mode(link_ksettings, advertising, Asym_Pause);
}
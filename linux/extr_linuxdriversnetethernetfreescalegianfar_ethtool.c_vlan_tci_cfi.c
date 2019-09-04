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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_tci; } ;
struct ethtool_rx_flow_spec {TYPE_1__ h_ext; } ;

/* Variables and functions */
 int VLAN_CFI_MASK ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 vlan_tci_cfi(struct ethtool_rx_flow_spec *rule)
{
	return be16_to_cpu(rule->h_ext.vlan_tci) & VLAN_CFI_MASK;
}
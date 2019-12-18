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
struct TYPE_4__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  vlan_etype; } ;
struct TYPE_3__ {int* hdata; } ;
struct ethtool_rx_flow_spec {TYPE_2__ m_ext; TYPE_1__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_invert_masks(struct ethtool_rx_flow_spec *flow)
{
	unsigned int i;

	for (i = 0; i < sizeof(flow->m_u); i++)
		flow->m_u.hdata[i] ^= 0xff;

	flow->m_ext.vlan_etype ^= cpu_to_be16(~0);
	flow->m_ext.vlan_tci ^= cpu_to_be16(~0);
	flow->m_ext.data[0] ^= cpu_to_be32(~0);
	flow->m_ext.data[1] ^= cpu_to_be32(~0);
}
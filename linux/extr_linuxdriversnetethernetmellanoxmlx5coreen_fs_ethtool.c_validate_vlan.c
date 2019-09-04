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
struct TYPE_4__ {int /*<<< orphan*/  vlan_tci; } ;
struct TYPE_3__ {scalar_t__ vlan_tci; scalar_t__ vlan_etype; } ;
struct ethtool_rx_flow_spec {TYPE_2__ h_ext; TYPE_1__ m_ext; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VLAN_N_VID ; 
 int /*<<< orphan*/  VLAN_VID_MASK ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_vlan(struct ethtool_rx_flow_spec *fs)
{
	if (fs->m_ext.vlan_etype ||
	    fs->m_ext.vlan_tci != cpu_to_be16(VLAN_VID_MASK))
		return -EINVAL;

	if (fs->m_ext.vlan_tci &&
	    (be16_to_cpu(fs->h_ext.vlan_tci) >= VLAN_N_VID))
		return -EINVAL;

	return 1;
}
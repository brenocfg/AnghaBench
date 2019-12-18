#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union ib_flow_spec {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_ip; } ;
struct ib_flow_spec_ipv4 {TYPE_1__ val; } ;
struct TYPE_6__ {int /*<<< orphan*/  dst_mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  dst_mac; } ;
struct ib_flow_spec_eth {TYPE_3__ val; TYPE_2__ mask; } ;
struct ib_flow_attr {scalar_t__ type; int num_of_specs; } ;

/* Variables and functions */
 scalar_t__ IB_FLOW_ATTR_NORMAL ; 
 scalar_t__ IB_FLOW_SPEC_ETH ; 
 scalar_t__ IB_FLOW_SPEC_IPV4 ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool flow_is_multicast_only(const struct ib_flow_attr *ib_attr)
{
	union ib_flow_spec *flow_spec;

	if (ib_attr->type != IB_FLOW_ATTR_NORMAL ||
	    ib_attr->num_of_specs < 1)
		return false;

	flow_spec = (union ib_flow_spec *)(ib_attr + 1);
	if (flow_spec->type == IB_FLOW_SPEC_IPV4) {
		struct ib_flow_spec_ipv4 *ipv4_spec;

		ipv4_spec = (struct ib_flow_spec_ipv4 *)flow_spec;
		if (ipv4_is_multicast(ipv4_spec->val.dst_ip))
			return true;

		return false;
	}

	if (flow_spec->type == IB_FLOW_SPEC_ETH) {
		struct ib_flow_spec_eth *eth_spec;

		eth_spec = (struct ib_flow_spec_eth *)flow_spec;
		return is_multicast_ether_addr(eth_spec->mask.dst_mac) &&
		       is_multicast_ether_addr(eth_spec->val.dst_mac);
	}

	return false;
}
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
struct tc_cls_flower_offload {int /*<<< orphan*/  dissector; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ICMP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfp_flower_check_higher_than_mac(struct tc_cls_flower_offload *f)
{
	return dissector_uses_key(f->dissector,
				  FLOW_DISSECTOR_KEY_IPV4_ADDRS) ||
		dissector_uses_key(f->dissector,
				   FLOW_DISSECTOR_KEY_IPV6_ADDRS) ||
		dissector_uses_key(f->dissector,
				   FLOW_DISSECTOR_KEY_PORTS) ||
		dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ICMP);
}
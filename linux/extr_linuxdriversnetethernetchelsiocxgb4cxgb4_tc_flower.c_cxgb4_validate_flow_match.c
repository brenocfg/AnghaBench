#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; TYPE_1__* dissector; int /*<<< orphan*/  key; } ;
struct net_device {int dummy; } ;
struct flow_dissector_key_ip {scalar_t__ ttl; } ;
struct flow_dissector_key_basic {int /*<<< orphan*/  n_proto; } ;
struct TYPE_3__ {int used_keys; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 scalar_t__ dissector_uses_key (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4_validate_flow_match(struct net_device *dev,
				     struct tc_cls_flower_offload *cls)
{
	u16 ethtype_mask = 0;
	u16 ethtype_key = 0;

	if (cls->dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IP))) {
		netdev_warn(dev, "Unsupported key used: 0x%x\n",
			    cls->dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  cls->key);
		struct flow_dissector_key_basic *mask =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  cls->mask);
		ethtype_key = ntohs(key->n_proto);
		ethtype_mask = ntohs(mask->n_proto);
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_IP)) {
		u16 eth_ip_type = ethtype_key & ethtype_mask;
		struct flow_dissector_key_ip *mask;

		if (eth_ip_type != ETH_P_IP && eth_ip_type != ETH_P_IPV6) {
			netdev_err(dev, "IP Key supported only with IPv4/v6");
			return -EINVAL;
		}

		mask = skb_flow_dissector_target(cls->dissector,
						 FLOW_DISSECTOR_KEY_IP,
						 cls->mask);
		if (mask->ttl) {
			netdev_warn(dev, "ttl match unsupported for offload");
			return -EOPNOTSUPP;
		}
	}

	return 0;
}
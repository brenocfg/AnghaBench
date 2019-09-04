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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int MAX_ADDR_LEN ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t bond_get_slave_size(const struct net_device *bond_dev,
				  const struct net_device *slave_dev)
{
	return nla_total_size(sizeof(u8)) +	/* IFLA_BOND_SLAVE_STATE */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_SLAVE_MII_STATUS */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_SLAVE_LINK_FAILURE_COUNT */
		nla_total_size(MAX_ADDR_LEN) +	/* IFLA_BOND_SLAVE_PERM_HWADDR */
		nla_total_size(sizeof(u16)) +	/* IFLA_BOND_SLAVE_QUEUE_ID */
		nla_total_size(sizeof(u16)) +	/* IFLA_BOND_SLAVE_AD_AGGREGATOR_ID */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_SLAVE_AD_ACTOR_OPER_PORT_STATE */
		nla_total_size(sizeof(u16)) +	/* IFLA_BOND_SLAVE_AD_PARTNER_OPER_PORT_STATE */
		0;
}
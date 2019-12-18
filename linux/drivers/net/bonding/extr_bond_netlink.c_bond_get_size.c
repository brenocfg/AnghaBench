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
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t BOND_MAX_ARP_TARGETS ; 
 int ETH_ALEN ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t bond_get_size(const struct net_device *bond_dev)
{
	return nla_total_size(sizeof(u8)) +	/* IFLA_BOND_MODE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ACTIVE_SLAVE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_MIIMON */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_UPDELAY */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_DOWNDELAY */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_USE_CARRIER */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_INTERVAL */
						/* IFLA_BOND_ARP_IP_TARGET */
		nla_total_size(sizeof(struct nlattr)) +
		nla_total_size(sizeof(u32)) * BOND_MAX_ARP_TARGETS +
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_VALIDATE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_ALL_TARGETS */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_PRIMARY */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_PRIMARY_RESELECT */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_FAIL_OVER_MAC */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_XMIT_HASH_POLICY */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_RESEND_IGMP */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_NUM_PEER_NOTIF */
		nla_total_size(sizeof(u8)) +   /* IFLA_BOND_ALL_SLAVES_ACTIVE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_MIN_LINKS */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_LP_INTERVAL */
		nla_total_size(sizeof(u32)) +  /* IFLA_BOND_PACKETS_PER_SLAVE */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_AD_LACP_RATE */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_AD_SELECT */
		nla_total_size(sizeof(struct nlattr)) + /* IFLA_BOND_AD_INFO */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_AGGREGATOR */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_NUM_PORTS */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_ACTOR_KEY */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_PARTNER_KEY*/
		nla_total_size(ETH_ALEN) +    /* IFLA_BOND_AD_INFO_PARTNER_MAC*/
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_ACTOR_SYS_PRIO */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_USER_PORT_KEY */
		nla_total_size(ETH_ALEN) + /* IFLA_BOND_AD_ACTOR_SYSTEM */
		nla_total_size(sizeof(u8)) + /* IFLA_BOND_TLB_DYNAMIC_LB */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_PEER_NOTIF_DELAY */
		0;
}
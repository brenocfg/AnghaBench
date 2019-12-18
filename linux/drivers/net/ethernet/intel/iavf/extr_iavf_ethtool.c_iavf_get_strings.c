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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  iavf_get_priv_flag_strings (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_get_stat_strings (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iavf_get_strings(struct net_device *netdev, u32 sset, u8 *data)
{
	switch (sset) {
	case ETH_SS_STATS:
		iavf_get_stat_strings(netdev, data);
		break;
	case ETH_SS_PRIV_FLAGS:
		iavf_get_priv_flag_strings(netdev, data);
		break;
	default:
		break;
	}
}
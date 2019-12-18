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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int VNIC_STATS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vnic_gstrings_stats ; 

__attribute__((used)) static void vnic_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
	int i;

	if (stringset != ETH_SS_STATS)
		return;

	for (i = 0; i < VNIC_STATS_LEN; i++)
		memcpy(data + i * ETH_GSTRING_LEN,
		       vnic_gstrings_stats[i].stat_string,
		       ETH_GSTRING_LEN);
}
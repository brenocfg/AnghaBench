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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ETH_SS_PRIV_FLAGS ; 
 int ETH_SS_STATS ; 
 int /*<<< orphan*/  g_xgmac_stats_string ; 

__attribute__((used)) static int hns_xgmac_get_sset_count(int stringset)
{
	if (stringset == ETH_SS_STATS || stringset == ETH_SS_PRIV_FLAGS)
		return ARRAY_SIZE(g_xgmac_stats_string);

	return 0;
}
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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 size_t nla_total_size_64bit (int) ; 

size_t bond_3ad_stats_size(void)
{
	return nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_LACPDU_RX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_LACPDU_TX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_LACPDU_UNKNOWN_RX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_LACPDU_ILLEGAL_RX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_MARKER_RX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_MARKER_TX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_MARKER_RESP_RX */
	       nla_total_size_64bit(sizeof(u64)) + /* BOND_3AD_STAT_MARKER_RESP_TX */
	       nla_total_size_64bit(sizeof(u64)); /* BOND_3AD_STAT_MARKER_UNKNOWN_RX */
}
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
struct dfs_pattern_detector {int dummy; } ;
struct ath_dfs_pool_stats {int dummy; } ;

/* Variables and functions */
 struct ath_dfs_pool_stats global_dfs_pool_stats ; 

__attribute__((used)) static struct ath_dfs_pool_stats
dpd_get_stats(struct dfs_pattern_detector *dpd)
{
	return global_dfs_pool_stats;
}
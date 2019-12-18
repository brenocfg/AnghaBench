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
struct dfs_pattern_detector {scalar_t__ (* set_dfs_domain ) (struct dfs_pattern_detector*,int) ;struct ath_common* common; int /*<<< orphan*/  channel_detectors; } ;
struct ath_common {int dummy; } ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CFG80211_CERTIFICATION_ONUS ; 
 int /*<<< orphan*/  DFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 struct dfs_pattern_detector default_dpd ; 
 int /*<<< orphan*/  kfree (struct dfs_pattern_detector*) ; 
 struct dfs_pattern_detector* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dfs_pattern_detector*,int) ; 

struct dfs_pattern_detector *
dfs_pattern_detector_init(struct ath_common *common,
			  enum nl80211_dfs_regions region)
{
	struct dfs_pattern_detector *dpd;

	if (!IS_ENABLED(CONFIG_CFG80211_CERTIFICATION_ONUS))
		return NULL;

	dpd = kmalloc(sizeof(*dpd), GFP_KERNEL);
	if (dpd == NULL)
		return NULL;

	*dpd = default_dpd;
	INIT_LIST_HEAD(&dpd->channel_detectors);

	dpd->common = common;
	if (dpd->set_dfs_domain(dpd, region))
		return dpd;

	ath_dbg(common, DFS,"Could not set DFS domain to %d", region);
	kfree(dpd);
	return NULL;
}
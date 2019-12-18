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
struct mwifiex_private {int /*<<< orphan*/  dfs_dev_dir; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_DFS_ADD_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  debug_mask ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getlog ; 
 int /*<<< orphan*/  histogram ; 
 int /*<<< orphan*/  hscfg ; 
 int /*<<< orphan*/  info ; 
 int /*<<< orphan*/  memrw ; 
 int /*<<< orphan*/  mwifiex_dfs_dir ; 
 int /*<<< orphan*/  rdeeprom ; 
 int /*<<< orphan*/  regrdwr ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  timeshare_coex ; 
 int /*<<< orphan*/  verext ; 

void
mwifiex_dev_debugfs_init(struct mwifiex_private *priv)
{
	if (!mwifiex_dfs_dir || !priv)
		return;

	priv->dfs_dev_dir = debugfs_create_dir(priv->netdev->name,
					       mwifiex_dfs_dir);

	if (!priv->dfs_dev_dir)
		return;

	MWIFIEX_DFS_ADD_FILE(info);
	MWIFIEX_DFS_ADD_FILE(debug);
	MWIFIEX_DFS_ADD_FILE(getlog);
	MWIFIEX_DFS_ADD_FILE(regrdwr);
	MWIFIEX_DFS_ADD_FILE(rdeeprom);

	MWIFIEX_DFS_ADD_FILE(memrw);
	MWIFIEX_DFS_ADD_FILE(hscfg);
	MWIFIEX_DFS_ADD_FILE(histogram);
	MWIFIEX_DFS_ADD_FILE(debug_mask);
	MWIFIEX_DFS_ADD_FILE(timeshare_coex);
	MWIFIEX_DFS_ADD_FILE(reset);
	MWIFIEX_DFS_ADD_FILE(verext);
}
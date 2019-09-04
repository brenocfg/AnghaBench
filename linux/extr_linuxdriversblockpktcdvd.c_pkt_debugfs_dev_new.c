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
struct pktcdvd_device {int /*<<< orphan*/  dfs_d_root; int /*<<< orphan*/  dfs_f_info; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct pktcdvd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_debugfs_root ; 

__attribute__((used)) static void pkt_debugfs_dev_new(struct pktcdvd_device *pd)
{
	if (!pkt_debugfs_root)
		return;
	pd->dfs_d_root = debugfs_create_dir(pd->name, pkt_debugfs_root);
	if (!pd->dfs_d_root)
		return;

	pd->dfs_f_info = debugfs_create_file("info", 0444,
					     pd->dfs_d_root, pd, &debug_fops);
}
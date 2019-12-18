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
struct pdc_state {int pdc_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,scalar_t__,struct pdc_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ debugfs_dir ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  pdc_debugfs_stats ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void pdc_setup_debugfs(struct pdc_state *pdcs)
{
	char spu_stats_name[16];

	if (!debugfs_initialized())
		return;

	snprintf(spu_stats_name, 16, "pdc%d_stats", pdcs->pdc_idx);
	if (!debugfs_dir)
		debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, NULL);

	/* S_IRUSR == 0400 */
	debugfs_create_file(spu_stats_name, 0400, debugfs_dir, pdcs,
			    &pdc_debugfs_stats);
}
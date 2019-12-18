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
struct mbxfb_info {int /*<<< orphan*/  debugfs_dir; } ;
struct fb_info {struct mbxfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mbxfb_debugfs_remove(struct fb_info *fbi)
{
	struct mbxfb_info *mfbi = fbi->par;

	debugfs_remove_recursive(mfbi->debugfs_dir);
}
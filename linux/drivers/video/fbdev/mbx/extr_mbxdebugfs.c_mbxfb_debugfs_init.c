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
struct mbxfb_info {struct dentry* debugfs_dir; } ;
struct fb_info {struct mbxfb_info* par; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_fops ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct fb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_fops ; 
 int /*<<< orphan*/  gsctl_fops ; 
 int /*<<< orphan*/  misc_fops ; 
 int /*<<< orphan*/  sdram_fops ; 
 int /*<<< orphan*/  sysconf_fops ; 

__attribute__((used)) static void mbxfb_debugfs_init(struct fb_info *fbi)
{
	struct mbxfb_info *mfbi = fbi->par;
	struct dentry *dir;

	dir = debugfs_create_dir("mbxfb", NULL);
	mfbi->debugfs_dir = dir;

	debugfs_create_file("sysconf", 0444, dir, fbi, &sysconf_fops);
	debugfs_create_file("clock", 0444, dir, fbi, &clock_fops);
	debugfs_create_file("display", 0444, dir, fbi, &display_fops);
	debugfs_create_file("gsctl", 0444, dir, fbi, &gsctl_fops);
	debugfs_create_file("sdram", 0444, dir, fbi, &sdram_fops);
	debugfs_create_file("misc", 0444, dir, fbi, &misc_fops);
}
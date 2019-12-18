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
struct intel_lpss {struct dentry* debugfs; int /*<<< orphan*/  idle_ltr; int /*<<< orphan*/  active_ltr; int /*<<< orphan*/  caps; int /*<<< orphan*/  dev; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lpss_cache_ltr (struct intel_lpss*) ; 
 int /*<<< orphan*/  intel_lpss_debugfs ; 

__attribute__((used)) static int intel_lpss_debugfs_add(struct intel_lpss *lpss)
{
	struct dentry *dir;

	dir = debugfs_create_dir(dev_name(lpss->dev), intel_lpss_debugfs);
	if (IS_ERR(dir))
		return PTR_ERR(dir);

	/* Cache the values into lpss structure */
	intel_lpss_cache_ltr(lpss);

	debugfs_create_x32("capabilities", S_IRUGO, dir, &lpss->caps);
	debugfs_create_x32("active_ltr", S_IRUGO, dir, &lpss->active_ltr);
	debugfs_create_x32("idle_ltr", S_IRUGO, dir, &lpss->idle_ltr);

	lpss->debugfs = dir;
	return 0;
}
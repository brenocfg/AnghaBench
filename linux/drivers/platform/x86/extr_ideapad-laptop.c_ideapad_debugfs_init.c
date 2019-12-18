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
struct ideapad_private {struct dentry* debug; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_cfg_fops ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct ideapad_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_status_fops ; 

__attribute__((used)) static void ideapad_debugfs_init(struct ideapad_private *priv)
{
	struct dentry *dir;

	dir = debugfs_create_dir("ideapad", NULL);
	priv->debug = dir;

	debugfs_create_file("cfg", S_IRUGO, dir, priv, &debugfs_cfg_fops);
	debugfs_create_file("status", S_IRUGO, dir, priv, &debugfs_status_fops);
}
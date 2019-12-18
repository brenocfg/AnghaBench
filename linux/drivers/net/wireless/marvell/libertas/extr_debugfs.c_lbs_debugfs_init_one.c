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
struct net_device {char* name; } ;
struct lbs_private {void* regs_dir; void** debugfs_regs_files; void* debugfs_dir; void* events_dir; void** debugfs_events_files; void** debugfs_files; } ;
struct lbs_debugfs_files {int /*<<< orphan*/  fops; int /*<<< orphan*/  perm; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lbs_debugfs_files*) ; 
 void* debugfs_create_dir (char*,void*) ; 
 void* debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct lbs_private*,int /*<<< orphan*/ *) ; 
 struct lbs_debugfs_files* debugfs_events_files ; 
 struct lbs_debugfs_files* debugfs_files ; 
 struct lbs_debugfs_files* debugfs_regs_files ; 
 int /*<<< orphan*/  lbs_debug_init (struct lbs_private*) ; 
 void* lbs_dir ; 

void lbs_debugfs_init_one(struct lbs_private *priv, struct net_device *dev)
{
	int i;
	const struct lbs_debugfs_files *files;
	if (!lbs_dir)
		goto exit;

	priv->debugfs_dir = debugfs_create_dir(dev->name, lbs_dir);

	for (i=0; i<ARRAY_SIZE(debugfs_files); i++) {
		files = &debugfs_files[i];
		priv->debugfs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->debugfs_dir,
							     priv,
							     &files->fops);
	}

	priv->events_dir = debugfs_create_dir("subscribed_events", priv->debugfs_dir);

	for (i=0; i<ARRAY_SIZE(debugfs_events_files); i++) {
		files = &debugfs_events_files[i];
		priv->debugfs_events_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->events_dir,
							     priv,
							     &files->fops);
	}

	priv->regs_dir = debugfs_create_dir("registers", priv->debugfs_dir);

	for (i=0; i<ARRAY_SIZE(debugfs_regs_files); i++) {
		files = &debugfs_regs_files[i];
		priv->debugfs_regs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->regs_dir,
							     priv,
							     &files->fops);
	}

#ifdef PROC_DEBUG
	lbs_debug_init(priv);
#endif
exit:
	return;
}
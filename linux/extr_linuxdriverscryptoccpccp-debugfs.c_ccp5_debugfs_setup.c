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
struct dentry {int dummy; } ;
struct ccp_device {char* name; int cmd_q_count; int id; struct dentry* debugfs_instance; struct ccp_device* cmd_q; } ;
struct ccp_cmd_queue {char* name; int cmd_q_count; int id; struct dentry* debugfs_instance; struct ccp_cmd_queue* cmd_q; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 int MAX_NAME_LEN ; 
 struct dentry* ccp_debugfs_dir ; 
 int /*<<< orphan*/  ccp_debugfs_info_ops ; 
 int /*<<< orphan*/  ccp_debugfs_lock ; 
 int /*<<< orphan*/  ccp_debugfs_queue_ops ; 
 int /*<<< orphan*/  ccp_debugfs_stats_ops ; 
 void* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct ccp_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void ccp5_debugfs_setup(struct ccp_device *ccp)
{
	struct ccp_cmd_queue *cmd_q;
	char name[MAX_NAME_LEN + 1];
	struct dentry *debugfs_info;
	struct dentry *debugfs_stats;
	struct dentry *debugfs_q_instance;
	struct dentry *debugfs_q_stats;
	int i;

	if (!debugfs_initialized())
		return;

	mutex_lock(&ccp_debugfs_lock);
	if (!ccp_debugfs_dir)
		ccp_debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, NULL);
	mutex_unlock(&ccp_debugfs_lock);
	if (!ccp_debugfs_dir)
		return;

	ccp->debugfs_instance = debugfs_create_dir(ccp->name, ccp_debugfs_dir);
	if (!ccp->debugfs_instance)
		goto err;

	debugfs_info = debugfs_create_file("info", 0400,
					   ccp->debugfs_instance, ccp,
					   &ccp_debugfs_info_ops);
	if (!debugfs_info)
		goto err;

	debugfs_stats = debugfs_create_file("stats", 0600,
					    ccp->debugfs_instance, ccp,
					    &ccp_debugfs_stats_ops);
	if (!debugfs_stats)
		goto err;

	for (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		snprintf(name, MAX_NAME_LEN - 1, "q%d", cmd_q->id);

		debugfs_q_instance =
			debugfs_create_dir(name, ccp->debugfs_instance);
		if (!debugfs_q_instance)
			goto err;

		debugfs_q_stats =
			debugfs_create_file("stats", 0600,
					    debugfs_q_instance, cmd_q,
					    &ccp_debugfs_queue_ops);
		if (!debugfs_q_stats)
			goto err;
	}

	return;

err:
	debugfs_remove_recursive(ccp->debugfs_instance);
}
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
struct vas_instance {int vas_id; struct dentry* dbgdir; int /*<<< orphan*/ * dbgname; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  vas_debugfs ; 
 int /*<<< orphan*/  vas_init_dbgdir () ; 

void vas_instance_init_dbgdir(struct vas_instance *vinst)
{
	struct dentry *d;

	vas_init_dbgdir();
	if (!vas_debugfs)
		return;

	vinst->dbgname = kzalloc(16, GFP_KERNEL);
	if (!vinst->dbgname)
		return;

	snprintf(vinst->dbgname, 16, "v%d", vinst->vas_id);

	d = debugfs_create_dir(vinst->dbgname, vas_debugfs);
	if (IS_ERR(d))
		goto free_name;

	vinst->dbgdir = d;
	return;

free_name:
	kfree(vinst->dbgname);
	vinst->dbgname = NULL;
	vinst->dbgdir = NULL;
}
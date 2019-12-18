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
typedef  int u8 ;
struct svc_debugfs_pwrmon_rail {int id; struct gb_svc* svc; int /*<<< orphan*/ * name; } ;
struct gb_svc_pwrmon_rail_names_get_response {int id; struct gb_svc* svc; int /*<<< orphan*/ * name; } ;
struct gb_svc {struct svc_debugfs_pwrmon_rail* pwrmon_rails; struct dentry* debugfs_dentry; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int GB_SVC_PWRMON_MAX_RAIL_COUNT ; 
 int GB_SVC_PWRMON_RAIL_NAME_BUFSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct svc_debugfs_pwrmon_rail*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 scalar_t__ gb_svc_pwrmon_rail_count_get (struct gb_svc*,int*) ; 
 scalar_t__ gb_svc_pwrmon_rail_names_get (struct gb_svc*,struct svc_debugfs_pwrmon_rail*,size_t) ; 
 struct svc_debugfs_pwrmon_rail* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct svc_debugfs_pwrmon_rail*) ; 
 struct svc_debugfs_pwrmon_rail* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrmon_debugfs_current_fops ; 
 int /*<<< orphan*/  pwrmon_debugfs_power_fops ; 
 int /*<<< orphan*/  pwrmon_debugfs_voltage_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void gb_svc_pwrmon_debugfs_init(struct gb_svc *svc)
{
	int i;
	size_t bufsize;
	struct dentry *dent;
	struct gb_svc_pwrmon_rail_names_get_response *rail_names;
	u8 rail_count;

	dent = debugfs_create_dir("pwrmon", svc->debugfs_dentry);
	if (IS_ERR_OR_NULL(dent))
		return;

	if (gb_svc_pwrmon_rail_count_get(svc, &rail_count))
		goto err_pwrmon_debugfs;

	if (!rail_count || rail_count > GB_SVC_PWRMON_MAX_RAIL_COUNT)
		goto err_pwrmon_debugfs;

	bufsize = sizeof(*rail_names) +
		GB_SVC_PWRMON_RAIL_NAME_BUFSIZE * rail_count;

	rail_names = kzalloc(bufsize, GFP_KERNEL);
	if (!rail_names)
		goto err_pwrmon_debugfs;

	svc->pwrmon_rails = kcalloc(rail_count, sizeof(*svc->pwrmon_rails),
				    GFP_KERNEL);
	if (!svc->pwrmon_rails)
		goto err_pwrmon_debugfs_free;

	if (gb_svc_pwrmon_rail_names_get(svc, rail_names, bufsize))
		goto err_pwrmon_debugfs_free;

	for (i = 0; i < rail_count; i++) {
		struct dentry *dir;
		struct svc_debugfs_pwrmon_rail *rail = &svc->pwrmon_rails[i];
		char fname[GB_SVC_PWRMON_RAIL_NAME_BUFSIZE];

		snprintf(fname, sizeof(fname), "%s",
			 (char *)&rail_names->name[i]);

		rail->id = i;
		rail->svc = svc;

		dir = debugfs_create_dir(fname, dent);
		debugfs_create_file("voltage_now", 0444, dir, rail,
				    &pwrmon_debugfs_voltage_fops);
		debugfs_create_file("current_now", 0444, dir, rail,
				    &pwrmon_debugfs_current_fops);
		debugfs_create_file("power_now", 0444, dir, rail,
				    &pwrmon_debugfs_power_fops);
	}

	kfree(rail_names);
	return;

err_pwrmon_debugfs_free:
	kfree(rail_names);
	kfree(svc->pwrmon_rails);
	svc->pwrmon_rails = NULL;

err_pwrmon_debugfs:
	debugfs_remove(dent);
}
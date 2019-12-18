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
struct qib_pportdata {int /*<<< orphan*/  pport_kobj; int /*<<< orphan*/  sl2vl_kobj; int /*<<< orphan*/  pport_cc_kobj; scalar_t__ congestion_entries_shadow; } ;
struct qib_devdata {int num_pports; struct qib_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc_setting_bin_attr ; 
 int /*<<< orphan*/  cc_table_bin_attr ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 scalar_t__ qib_cc_table_size ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qib_verbs_unregister_sysfs(struct qib_devdata *dd)
{
	struct qib_pportdata *ppd;
	int i;

	for (i = 0; i < dd->num_pports; i++) {
		ppd = &dd->pport[i];
		if (qib_cc_table_size &&
			ppd->congestion_entries_shadow) {
			sysfs_remove_bin_file(&ppd->pport_cc_kobj,
				&cc_setting_bin_attr);
			sysfs_remove_bin_file(&ppd->pport_cc_kobj,
				&cc_table_bin_attr);
			kobject_put(&ppd->pport_cc_kobj);
		}
		kobject_put(&ppd->sl2vl_kobj);
		kobject_put(&ppd->pport_kobj);
	}
}
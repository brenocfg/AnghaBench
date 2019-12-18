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
struct hfi1_pportdata {int /*<<< orphan*/  sc2vl_kobj; int /*<<< orphan*/  sl2sc_kobj; int /*<<< orphan*/  vl2mtu_kobj; int /*<<< orphan*/  pport_cc_kobj; } ;
struct hfi1_devdata {int num_pports; struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc_setting_bin_attr ; 
 int /*<<< orphan*/  cc_table_bin_attr ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void hfi1_verbs_unregister_sysfs(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	int i;

	for (i = 0; i < dd->num_pports; i++) {
		ppd = &dd->pport[i];

		sysfs_remove_bin_file(&ppd->pport_cc_kobj,
				      &cc_setting_bin_attr);
		sysfs_remove_bin_file(&ppd->pport_cc_kobj,
				      &cc_table_bin_attr);
		kobject_put(&ppd->pport_cc_kobj);
		kobject_put(&ppd->vl2mtu_kobj);
		kobject_put(&ppd->sl2sc_kobj);
		kobject_put(&ppd->sc2vl_kobj);
	}
}
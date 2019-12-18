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
struct kobject {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  sc2vl_kobj; int /*<<< orphan*/  sl2sc_kobj; int /*<<< orphan*/  vl2mtu_kobj; int /*<<< orphan*/  pport_cc_kobj; } ;
struct hfi1_devdata {int num_pports; struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  cc_setting_bin_attr ; 
 int /*<<< orphan*/  cc_table_bin_attr ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int,...) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  hfi1_sc2vl_ktype ; 
 int /*<<< orphan*/  hfi1_sl2sc_ktype ; 
 int /*<<< orphan*/  hfi1_vl2mtu_ktype ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct kobject*,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_cc_ktype ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hfi1_create_port_files(struct ib_device *ibdev, u8 port_num,
			   struct kobject *kobj)
{
	struct hfi1_pportdata *ppd;
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	int ret;

	if (!port_num || port_num > dd->num_pports) {
		dd_dev_err(dd,
			   "Skipping infiniband class with invalid port %u\n",
			   port_num);
		return -ENODEV;
	}
	ppd = &dd->pport[port_num - 1];

	ret = kobject_init_and_add(&ppd->sc2vl_kobj, &hfi1_sc2vl_ktype, kobj,
				   "sc2vl");
	if (ret) {
		dd_dev_err(dd,
			   "Skipping sc2vl sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail;
	}
	kobject_uevent(&ppd->sc2vl_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->sl2sc_kobj, &hfi1_sl2sc_ktype, kobj,
				   "sl2sc");
	if (ret) {
		dd_dev_err(dd,
			   "Skipping sl2sc sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail_sc2vl;
	}
	kobject_uevent(&ppd->sl2sc_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->vl2mtu_kobj, &hfi1_vl2mtu_ktype, kobj,
				   "vl2mtu");
	if (ret) {
		dd_dev_err(dd,
			   "Skipping vl2mtu sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail_sl2sc;
	}
	kobject_uevent(&ppd->vl2mtu_kobj, KOBJ_ADD);

	ret = kobject_init_and_add(&ppd->pport_cc_kobj, &port_cc_ktype,
				   kobj, "CCMgtA");
	if (ret) {
		dd_dev_err(dd,
			   "Skipping Congestion Control sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail_vl2mtu;
	}

	kobject_uevent(&ppd->pport_cc_kobj, KOBJ_ADD);

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj, &cc_setting_bin_attr);
	if (ret) {
		dd_dev_err(dd,
			   "Skipping Congestion Control setting sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail_cc;
	}

	ret = sysfs_create_bin_file(&ppd->pport_cc_kobj, &cc_table_bin_attr);
	if (ret) {
		dd_dev_err(dd,
			   "Skipping Congestion Control table sysfs info, (err %d) port %u\n",
			   ret, port_num);
		goto bail_cc_entry_bin;
	}

	dd_dev_info(dd,
		    "Congestion Control Agent enabled for port %d\n",
		    port_num);

	return 0;

bail_cc_entry_bin:
	sysfs_remove_bin_file(&ppd->pport_cc_kobj,
			      &cc_setting_bin_attr);
bail_cc:
	kobject_put(&ppd->pport_cc_kobj);
bail_vl2mtu:
	kobject_put(&ppd->vl2mtu_kobj);
bail_sl2sc:
	kobject_put(&ppd->sl2sc_kobj);
bail_sc2vl:
	kobject_put(&ppd->sc2vl_kobj);
bail:
	return ret;
}
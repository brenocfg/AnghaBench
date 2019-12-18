#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_25__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_23__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct occ_poll_response_header {int status; int ext_status; scalar_t__ occs_present; } ;
struct TYPE_36__ {scalar_t__ data; } ;
struct occ {int prev_stat; int prev_ext_stat; scalar_t__ prev_occs_present; scalar_t__ error; scalar_t__ prev_error; TYPE_17__* bus_dev; int /*<<< orphan*/  hwmon; TYPE_1__ resp; } ;
struct TYPE_49__ {char* name; } ;
struct TYPE_50__ {TYPE_8__ attr; } ;
struct TYPE_47__ {char* name; } ;
struct TYPE_48__ {TYPE_6__ attr; } ;
struct TYPE_45__ {char* name; } ;
struct TYPE_46__ {TYPE_4__ attr; } ;
struct TYPE_43__ {char* name; } ;
struct TYPE_44__ {TYPE_2__ attr; } ;
struct TYPE_32__ {char* name; } ;
struct TYPE_42__ {TYPE_16__ attr; } ;
struct TYPE_41__ {TYPE_5__ dev_attr; } ;
struct TYPE_40__ {TYPE_7__ dev_attr; } ;
struct TYPE_39__ {TYPE_9__ dev_attr; } ;
struct TYPE_38__ {TYPE_3__ dev_attr; } ;
struct TYPE_26__ {char* name; } ;
struct TYPE_27__ {TYPE_10__ attr; } ;
struct TYPE_37__ {TYPE_11__ dev_attr; } ;
struct TYPE_28__ {char* name; } ;
struct TYPE_29__ {TYPE_12__ attr; } ;
struct TYPE_35__ {TYPE_13__ dev_attr; } ;
struct TYPE_30__ {char* name; } ;
struct TYPE_31__ {TYPE_14__ attr; } ;
struct TYPE_34__ {TYPE_15__ dev_attr; } ;
struct TYPE_33__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int OCC_EXT_STAT_DVFS_OT ; 
 int OCC_EXT_STAT_DVFS_POWER ; 
 int OCC_EXT_STAT_MEM_THROTTLE ; 
 int OCC_EXT_STAT_QUICK_DROP ; 
 int OCC_STAT_ACTIVE ; 
 int OCC_STAT_MASTER ; 
 TYPE_25__ dev_attr_occ_error ; 
 TYPE_24__ sensor_dev_attr_occ_active ; 
 TYPE_23__ sensor_dev_attr_occ_dvfs_overtemp ; 
 TYPE_22__ sensor_dev_attr_occ_dvfs_power ; 
 TYPE_21__ sensor_dev_attr_occ_master ; 
 TYPE_20__ sensor_dev_attr_occ_mem_throttle ; 
 TYPE_19__ sensor_dev_attr_occ_quick_pwr_drop ; 
 TYPE_18__ sensor_dev_attr_occs_present ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void occ_sysfs_poll_done(struct occ *occ)
{
	const char *name;
	struct occ_poll_response_header *header =
		(struct occ_poll_response_header *)occ->resp.data;

	/*
	 * On the first poll response, we haven't yet created the sysfs
	 * attributes, so don't make any notify calls.
	 */
	if (!occ->hwmon)
		goto done;

	if ((header->status & OCC_STAT_MASTER) !=
	    (occ->prev_stat & OCC_STAT_MASTER)) {
		name = sensor_dev_attr_occ_master.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->status & OCC_STAT_ACTIVE) !=
	    (occ->prev_stat & OCC_STAT_ACTIVE)) {
		name = sensor_dev_attr_occ_active.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->ext_status & OCC_EXT_STAT_DVFS_OT) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_DVFS_OT)) {
		name = sensor_dev_attr_occ_dvfs_overtemp.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->ext_status & OCC_EXT_STAT_DVFS_POWER) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_DVFS_POWER)) {
		name = sensor_dev_attr_occ_dvfs_power.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->ext_status & OCC_EXT_STAT_MEM_THROTTLE) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_MEM_THROTTLE)) {
		name = sensor_dev_attr_occ_mem_throttle.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->ext_status & OCC_EXT_STAT_QUICK_DROP) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_QUICK_DROP)) {
		name = sensor_dev_attr_occ_quick_pwr_drop.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if ((header->status & OCC_STAT_MASTER) &&
	    header->occs_present != occ->prev_occs_present) {
		name = sensor_dev_attr_occs_present.dev_attr.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	if (occ->error && occ->error != occ->prev_error) {
		name = dev_attr_occ_error.attr.name;
		sysfs_notify(&occ->bus_dev->kobj, NULL, name);
	}

	/* no notifications for OCC state; doesn't indicate error condition */

done:
	occ->prev_error = occ->error;
	occ->prev_stat = header->status;
	occ->prev_ext_stat = header->ext_status;
	occ->prev_occs_present = header->occs_present;
}
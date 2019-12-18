#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * type; int /*<<< orphan*/  groups; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {scalar_t__ st; TYPE_2__ dev; int /*<<< orphan*/  driver; TYPE_1__ schid; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 scalar_t__ SUBCHANNEL_TYPE_IO ; 
 TYPE_3__** channel_subsystems ; 
 int /*<<< orphan*/  css_bus_type ; 
 int css_sch_device_register (struct subchannel*) ; 
 int /*<<< orphan*/  css_update_ssd_info (struct subchannel*) ; 
 int /*<<< orphan*/  default_subch_attr_groups ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_2__*,int) ; 
 int /*<<< orphan*/  io_subchannel_type ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int css_register_subchannel(struct subchannel *sch)
{
	int ret;

	/* Initialize the subchannel structure */
	sch->dev.parent = &channel_subsystems[0]->device;
	sch->dev.bus = &css_bus_type;
	sch->dev.groups = default_subch_attr_groups;

	if (sch->st == SUBCHANNEL_TYPE_IO)
		sch->dev.type = &io_subchannel_type;

	/*
	 * We don't want to generate uevents for I/O subchannels that don't
	 * have a working ccw device behind them since they will be
	 * unregistered before they can be used anyway, so we delay the add
	 * uevent until after device recognition was successful.
	 * Note that we suppress the uevent for all subchannel types;
	 * the subchannel driver can decide itself when it wants to inform
	 * userspace of its existence.
	 */
	dev_set_uevent_suppress(&sch->dev, 1);
	css_update_ssd_info(sch);
	/* make it known to the system */
	ret = css_sch_device_register(sch);
	if (ret) {
		CIO_MSG_EVENT(0, "Could not register sch 0.%x.%04x: %d\n",
			      sch->schid.ssid, sch->schid.sch_no, ret);
		return ret;
	}
	if (!sch->driver) {
		/*
		 * No driver matched. Generate the uevent now so that
		 * a fitting driver module may be loaded based on the
		 * modalias.
		 */
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	}
	return ret;
}
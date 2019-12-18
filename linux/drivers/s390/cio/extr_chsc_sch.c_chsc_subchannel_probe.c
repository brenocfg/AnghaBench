#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {TYPE_2__ dev; TYPE_1__ schid; int /*<<< orphan*/  isc; } ;
struct chsc_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_MSG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CHSC_SCH_ISC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_uevent_suppress (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct chsc_private*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chsc_private*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chsc_private* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chsc_subchannel_probe(struct subchannel *sch)
{
	struct chsc_private *private;
	int ret;

	CHSC_MSG(6, "Detected chsc subchannel 0.%x.%04x\n",
		 sch->schid.ssid, sch->schid.sch_no);
	sch->isc = CHSC_SCH_ISC;
	private = kzalloc(sizeof(*private), GFP_KERNEL);
	if (!private)
		return -ENOMEM;
	dev_set_drvdata(&sch->dev, private);
	ret = cio_enable_subchannel(sch, (u32)(unsigned long)sch);
	if (ret) {
		CHSC_MSG(0, "Failed to enable 0.%x.%04x: %d\n",
			 sch->schid.ssid, sch->schid.sch_no, ret);
		dev_set_drvdata(&sch->dev, NULL);
		kfree(private);
	} else {
		if (dev_get_uevent_suppress(&sch->dev)) {
			dev_set_uevent_suppress(&sch->dev, 0);
			kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
		}
	}
	return ret;
}
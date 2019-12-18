#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  dev; TYPE_1__ schid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int css_sch_device_register(struct subchannel *sch)
{
	int ret;

	mutex_lock(&sch->reg_mutex);
	dev_set_name(&sch->dev, "0.%x.%04x", sch->schid.ssid,
		     sch->schid.sch_no);
	ret = device_add(&sch->dev);
	mutex_unlock(&sch->reg_mutex);
	return ret;
}
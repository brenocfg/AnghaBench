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
struct kobj_uevent_env {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  swbit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  propbit; scalar_t__ uniq; scalar_t__ phys; scalar_t__ name; TYPE_1__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MAX ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_LED ; 
 int /*<<< orphan*/  EV_MAX ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  FF_MAX ; 
 int /*<<< orphan*/  INPUT_ADD_HOTPLUG_BM_VAR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_ADD_HOTPLUG_MODALIAS_VAR (struct input_dev*) ; 
 int /*<<< orphan*/  INPUT_ADD_HOTPLUG_VAR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  INPUT_PROP_MAX ; 
 int /*<<< orphan*/  KEY_MAX ; 
 int /*<<< orphan*/  LED_MAX ; 
 int /*<<< orphan*/  MSC_MAX ; 
 int /*<<< orphan*/  REL_MAX ; 
 int /*<<< orphan*/  SND_MAX ; 
 int /*<<< orphan*/  SW_MAX ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_dev* to_input_dev (struct device*) ; 

__attribute__((used)) static int input_dev_uevent(struct device *device, struct kobj_uevent_env *env)
{
	struct input_dev *dev = to_input_dev(device);

	INPUT_ADD_HOTPLUG_VAR("PRODUCT=%x/%x/%x/%x",
				dev->id.bustype, dev->id.vendor,
				dev->id.product, dev->id.version);
	if (dev->name)
		INPUT_ADD_HOTPLUG_VAR("NAME=\"%s\"", dev->name);
	if (dev->phys)
		INPUT_ADD_HOTPLUG_VAR("PHYS=\"%s\"", dev->phys);
	if (dev->uniq)
		INPUT_ADD_HOTPLUG_VAR("UNIQ=\"%s\"", dev->uniq);

	INPUT_ADD_HOTPLUG_BM_VAR("PROP=", dev->propbit, INPUT_PROP_MAX);

	INPUT_ADD_HOTPLUG_BM_VAR("EV=", dev->evbit, EV_MAX);
	if (test_bit(EV_KEY, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("KEY=", dev->keybit, KEY_MAX);
	if (test_bit(EV_REL, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("REL=", dev->relbit, REL_MAX);
	if (test_bit(EV_ABS, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("ABS=", dev->absbit, ABS_MAX);
	if (test_bit(EV_MSC, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("MSC=", dev->mscbit, MSC_MAX);
	if (test_bit(EV_LED, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("LED=", dev->ledbit, LED_MAX);
	if (test_bit(EV_SND, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("SND=", dev->sndbit, SND_MAX);
	if (test_bit(EV_FF, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("FF=", dev->ffbit, FF_MAX);
	if (test_bit(EV_SW, dev->evbit))
		INPUT_ADD_HOTPLUG_BM_VAR("SW=", dev->swbit, SW_MAX);

	INPUT_ADD_HOTPLUG_MODALIAS_VAR(dev);

	return 0;
}
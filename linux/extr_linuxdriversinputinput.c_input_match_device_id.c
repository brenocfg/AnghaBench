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
struct input_device_id {int flags; scalar_t__ bustype; scalar_t__ vendor; scalar_t__ product; scalar_t__ version; int /*<<< orphan*/  propbit; int /*<<< orphan*/  swbit; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;
struct TYPE_2__ {scalar_t__ bustype; scalar_t__ vendor; scalar_t__ product; scalar_t__ version; } ;
struct input_dev {int /*<<< orphan*/  propbit; int /*<<< orphan*/  swbit; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MAX ; 
 int /*<<< orphan*/  EV_MAX ; 
 int /*<<< orphan*/  FF_MAX ; 
 int INPUT_DEVICE_ID_MATCH_BUS ; 
 int INPUT_DEVICE_ID_MATCH_PRODUCT ; 
 int INPUT_DEVICE_ID_MATCH_VENDOR ; 
 int INPUT_DEVICE_ID_MATCH_VERSION ; 
 int /*<<< orphan*/  INPUT_PROP_MAX ; 
 int /*<<< orphan*/  KEY_MAX ; 
 int /*<<< orphan*/  LED_MAX ; 
 int /*<<< orphan*/  MSC_MAX ; 
 int /*<<< orphan*/  REL_MAX ; 
 int /*<<< orphan*/  SND_MAX ; 
 int /*<<< orphan*/  SW_MAX ; 
 int /*<<< orphan*/  bitmap_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool input_match_device_id(const struct input_dev *dev,
			   const struct input_device_id *id)
{
	if (id->flags & INPUT_DEVICE_ID_MATCH_BUS)
		if (id->bustype != dev->id.bustype)
			return false;

	if (id->flags & INPUT_DEVICE_ID_MATCH_VENDOR)
		if (id->vendor != dev->id.vendor)
			return false;

	if (id->flags & INPUT_DEVICE_ID_MATCH_PRODUCT)
		if (id->product != dev->id.product)
			return false;

	if (id->flags & INPUT_DEVICE_ID_MATCH_VERSION)
		if (id->version != dev->id.version)
			return false;

	if (!bitmap_subset(id->evbit, dev->evbit, EV_MAX) ||
	    !bitmap_subset(id->keybit, dev->keybit, KEY_MAX) ||
	    !bitmap_subset(id->relbit, dev->relbit, REL_MAX) ||
	    !bitmap_subset(id->absbit, dev->absbit, ABS_MAX) ||
	    !bitmap_subset(id->mscbit, dev->mscbit, MSC_MAX) ||
	    !bitmap_subset(id->ledbit, dev->ledbit, LED_MAX) ||
	    !bitmap_subset(id->sndbit, dev->sndbit, SND_MAX) ||
	    !bitmap_subset(id->ffbit, dev->ffbit, FF_MAX) ||
	    !bitmap_subset(id->swbit, dev->swbit, SW_MAX) ||
	    !bitmap_subset(id->propbit, dev->propbit, INPUT_PROP_MAX)) {
		return false;
	}

	return true;
}
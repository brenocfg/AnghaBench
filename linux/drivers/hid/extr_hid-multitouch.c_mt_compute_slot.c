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
struct mt_usages {int* contactid; } ;
struct mt_device {int dummy; } ;
struct mt_application {int quirks; int num_received; } ;
struct input_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int MT_QUIRK_CYPRESS ; 
 int MT_QUIRK_SLOT_IS_CONTACTID ; 
 int MT_QUIRK_SLOT_IS_CONTACTID_MINUS_ONE ; 
 int MT_QUIRK_SLOT_IS_CONTACTNUMBER ; 
 int cypress_compute_slot (struct mt_application*,struct mt_usages*) ; 
 int input_mt_get_slot_by_key (struct input_dev*,int) ; 

__attribute__((used)) static int mt_compute_slot(struct mt_device *td, struct mt_application *app,
			   struct mt_usages *slot,
			   struct input_dev *input)
{
	__s32 quirks = app->quirks;

	if (quirks & MT_QUIRK_SLOT_IS_CONTACTID)
		return *slot->contactid;

	if (quirks & MT_QUIRK_CYPRESS)
		return cypress_compute_slot(app, slot);

	if (quirks & MT_QUIRK_SLOT_IS_CONTACTNUMBER)
		return app->num_received;

	if (quirks & MT_QUIRK_SLOT_IS_CONTACTID_MINUS_ONE)
		return *slot->contactid - 1;

	return input_mt_get_slot_by_key(input, *slot->contactid);
}
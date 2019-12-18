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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SM718 ; 
 int /*<<< orphan*/  SM750 ; 
 int /*<<< orphan*/  SM750LE ; 
 scalar_t__ SM750LE_REVISION_ID ; 
 int /*<<< orphan*/  SM_UNKNOWN ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void sm750_set_chip_type(unsigned short dev_id, u8 rev_id)
{
	if (dev_id == 0x718) {
		chip = SM718;
	} else if (dev_id == 0x750) {
		chip = SM750;
		/* SM750 and SM750LE are different in their revision ID only. */
		if (rev_id == SM750LE_REVISION_ID) {
			chip = SM750LE;
			pr_info("found sm750le\n");
		}
	} else {
		chip = SM_UNKNOWN;
	}
}
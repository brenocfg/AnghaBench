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
struct pn533_target_type_a {int /*<<< orphan*/  sel_res; int /*<<< orphan*/  sens_res; } ;

/* Variables and functions */
 scalar_t__ PN533_TYPE_A_SEL_CASCADE (int /*<<< orphan*/ ) ; 
 scalar_t__ PN533_TYPE_A_SENS_RES_PLATCONF (int /*<<< orphan*/ ) ; 
 scalar_t__ PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL ; 
 scalar_t__ PN533_TYPE_A_SENS_RES_SSD (int /*<<< orphan*/ ) ; 
 scalar_t__ PN533_TYPE_A_SENS_RES_SSD_JEWEL ; 

__attribute__((used)) static bool pn533_target_type_a_is_valid(struct pn533_target_type_a *type_a,
							int target_data_len)
{
	u8 ssd;
	u8 platconf;

	if (target_data_len < sizeof(struct pn533_target_type_a))
		return false;

	/*
	 * The length check of nfcid[] and ats[] are not being performed because
	 * the values are not being used
	 */

	/* Requirement 4.6.3.3 from NFC Forum Digital Spec */
	ssd = PN533_TYPE_A_SENS_RES_SSD(type_a->sens_res);
	platconf = PN533_TYPE_A_SENS_RES_PLATCONF(type_a->sens_res);

	if ((ssd == PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf != PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL) ||
	    (ssd != PN533_TYPE_A_SENS_RES_SSD_JEWEL &&
	     platconf == PN533_TYPE_A_SENS_RES_PLATCONF_JEWEL))
		return false;

	/* Requirements 4.8.2.1, 4.8.2.3, 4.8.2.5 and 4.8.2.7 from NFC Forum */
	if (PN533_TYPE_A_SEL_CASCADE(type_a->sel_res) != 0)
		return false;

	return true;
}
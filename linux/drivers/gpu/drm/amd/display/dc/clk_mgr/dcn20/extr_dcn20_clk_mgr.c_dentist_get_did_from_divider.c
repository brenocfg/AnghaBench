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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ DENTIST_BASE_DID_1 ; 
 scalar_t__ DENTIST_BASE_DID_2 ; 
 scalar_t__ DENTIST_BASE_DID_3 ; 
 scalar_t__ DENTIST_BASE_DID_4 ; 
 int DENTIST_DIVIDER_RANGE_1_START ; 
 int DENTIST_DIVIDER_RANGE_1_STEP ; 
 int DENTIST_DIVIDER_RANGE_2_START ; 
 int DENTIST_DIVIDER_RANGE_2_STEP ; 
 int DENTIST_DIVIDER_RANGE_3_START ; 
 int DENTIST_DIVIDER_RANGE_3_STEP ; 
 int DENTIST_DIVIDER_RANGE_4_START ; 
 int DENTIST_DIVIDER_RANGE_4_STEP ; 
 scalar_t__ DENTIST_MAX_DID ; 

uint32_t dentist_get_did_from_divider(int divider)
{
	uint32_t divider_id;

	/* we want to floor here to get higher clock than required rather than lower */
	if (divider < DENTIST_DIVIDER_RANGE_2_START) {
		if (divider < DENTIST_DIVIDER_RANGE_1_START)
			divider_id = DENTIST_BASE_DID_1;
		else
			divider_id = DENTIST_BASE_DID_1
				+ (divider - DENTIST_DIVIDER_RANGE_1_START)
					/ DENTIST_DIVIDER_RANGE_1_STEP;
	} else if (divider < DENTIST_DIVIDER_RANGE_3_START) {
		divider_id = DENTIST_BASE_DID_2
				+ (divider - DENTIST_DIVIDER_RANGE_2_START)
					/ DENTIST_DIVIDER_RANGE_2_STEP;
	} else if (divider < DENTIST_DIVIDER_RANGE_4_START) {
		divider_id = DENTIST_BASE_DID_3
				+ (divider - DENTIST_DIVIDER_RANGE_3_START)
					/ DENTIST_DIVIDER_RANGE_3_STEP;
	} else {
		divider_id = DENTIST_BASE_DID_4
				+ (divider - DENTIST_DIVIDER_RANGE_4_START)
					/ DENTIST_DIVIDER_RANGE_4_STEP;
		if (divider_id > DENTIST_MAX_DID)
			divider_id = DENTIST_MAX_DID;
	}

	return divider_id;
}
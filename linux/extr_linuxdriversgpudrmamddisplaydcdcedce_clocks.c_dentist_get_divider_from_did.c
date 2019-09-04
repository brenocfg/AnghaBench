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

/* Variables and functions */
 int DENTIST_BASE_DID_1 ; 
 int DENTIST_BASE_DID_2 ; 
 int DENTIST_BASE_DID_3 ; 
 int DENTIST_BASE_DID_4 ; 
 int DENTIST_DIVIDER_RANGE_1_START ; 
 int DENTIST_DIVIDER_RANGE_1_STEP ; 
 int DENTIST_DIVIDER_RANGE_2_START ; 
 int DENTIST_DIVIDER_RANGE_2_STEP ; 
 int DENTIST_DIVIDER_RANGE_3_START ; 
 int DENTIST_DIVIDER_RANGE_3_STEP ; 
 int DENTIST_DIVIDER_RANGE_4_START ; 
 int DENTIST_DIVIDER_RANGE_4_STEP ; 
 int DENTIST_MAX_DID ; 

__attribute__((used)) static int dentist_get_divider_from_did(int did)
{
	if (did < DENTIST_BASE_DID_1)
		did = DENTIST_BASE_DID_1;
	if (did > DENTIST_MAX_DID)
		did = DENTIST_MAX_DID;

	if (did < DENTIST_BASE_DID_2) {
		return DENTIST_DIVIDER_RANGE_1_START + DENTIST_DIVIDER_RANGE_1_STEP
							* (did - DENTIST_BASE_DID_1);
	} else if (did < DENTIST_BASE_DID_3) {
		return DENTIST_DIVIDER_RANGE_2_START + DENTIST_DIVIDER_RANGE_2_STEP
							* (did - DENTIST_BASE_DID_2);
	} else if (did < DENTIST_BASE_DID_4) {
		return DENTIST_DIVIDER_RANGE_3_START + DENTIST_DIVIDER_RANGE_3_STEP
							* (did - DENTIST_BASE_DID_3);
	} else {
		return DENTIST_DIVIDER_RANGE_4_START + DENTIST_DIVIDER_RANGE_4_STEP
							* (did - DENTIST_BASE_DID_4);
	}
}
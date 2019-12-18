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
struct ath_hw {int /*<<< orphan*/ * cal_list_curr; int /*<<< orphan*/ * cal_list; int /*<<< orphan*/  iq_caldata; int /*<<< orphan*/ * cal_list_last; struct ath9k_hw_cal_data* caldata; } ;
struct ath9k_hw_cal_data {scalar_t__ CalValid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_CAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSERT_CAL (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_reset_calibration (struct ath_hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar9003_hw_init_cal_common(struct ath_hw *ah)
{
	struct ath9k_hw_cal_data *caldata = ah->caldata;

	/* Initialize list pointers */
	ah->cal_list = ah->cal_list_last = ah->cal_list_curr = NULL;

	INIT_CAL(&ah->iq_caldata);
	INSERT_CAL(ah, &ah->iq_caldata);

	/* Initialize current pointer to first element in list */
	ah->cal_list_curr = ah->cal_list;

	if (ah->cal_list_curr)
		ath9k_hw_reset_calibration(ah, ah->cal_list_curr);

	if (caldata)
		caldata->CalValid = 0;
}
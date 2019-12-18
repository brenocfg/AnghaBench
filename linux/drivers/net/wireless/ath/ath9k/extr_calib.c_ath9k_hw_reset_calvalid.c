#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hw {int supp_cals; TYPE_3__* caldata; TYPE_2__* curchan; struct ath9k_cal_list* cal_list_curr; } ;
struct ath_common {int dummy; } ;
struct ath9k_cal_list {scalar_t__ calState; TYPE_4__* calData; } ;
struct TYPE_8__ {int calType; } ;
struct TYPE_7__ {int CalValid; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_9100 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9160_10_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 scalar_t__ CAL_DONE ; 
 scalar_t__ CAL_WAITING ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,...) ; 

bool ath9k_hw_reset_calvalid(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_cal_list *currCal = ah->cal_list_curr;

	if (!ah->caldata)
		return true;

	if (!AR_SREV_9100(ah) && !AR_SREV_9160_10_OR_LATER(ah))
		return true;

	if (currCal == NULL)
		return true;

	if (currCal->calState != CAL_DONE) {
		ath_dbg(common, CALIBRATE, "Calibration state incorrect, %d\n",
			currCal->calState);
		return true;
	}

	if (!(ah->supp_cals & currCal->calData->calType))
		return true;

	ath_dbg(common, CALIBRATE, "Resetting Cal %d state for channel %u\n",
		currCal->calData->calType, ah->curchan->chan->center_freq);

	ah->caldata->CalValid &= ~currCal->calData->calType;
	currCal->calState = CAL_WAITING;

	return false;
}
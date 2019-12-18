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
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ rssi_tolerance; } ;

/* Variables and functions */
 scalar_t__ COEX_RSSI_STATE_HIGH ; 
 scalar_t__ COEX_RSSI_STATE_LOW ; 
 scalar_t__ COEX_RSSI_STATE_STAY_HIGH ; 
 scalar_t__ COEX_RSSI_STATE_STAY_LOW ; 

__attribute__((used)) static u8 rtw_coex_next_rssi_state(struct rtw_dev *rtwdev, u8 pre_state,
				   u8 rssi, u8 rssi_thresh)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 tol = chip->rssi_tolerance;
	u8 next_state;

	if (pre_state == COEX_RSSI_STATE_LOW ||
	    pre_state == COEX_RSSI_STATE_STAY_LOW) {
		if (rssi >= (rssi_thresh + tol))
			next_state = COEX_RSSI_STATE_HIGH;
		else
			next_state = COEX_RSSI_STATE_STAY_LOW;
	} else {
		if (rssi < rssi_thresh)
			next_state = COEX_RSSI_STATE_LOW;
		else
			next_state = COEX_RSSI_STATE_STAY_HIGH;
	}

	return next_state;
}
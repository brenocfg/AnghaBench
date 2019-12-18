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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ OLC_FOR_AR9280_20_LATER ; 
 scalar_t__ OLC_FOR_AR9287_10_LATER ; 
 int /*<<< orphan*/  ar9280_hw_olc_temp_compensation (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9287_hw_olc_temp_compensation (struct ath_hw*) ; 

__attribute__((used)) static void ar9002_hw_olc_temp_compensation(struct ath_hw *ah)
{
	if (OLC_FOR_AR9287_10_LATER)
		ar9287_hw_olc_temp_compensation(ah);
	else if (OLC_FOR_AR9280_20_LATER)
		ar9280_hw_olc_temp_compensation(ah);
}
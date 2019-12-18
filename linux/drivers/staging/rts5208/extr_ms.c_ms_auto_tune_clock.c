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
struct ms_info {int ms_clock; } ;
struct rtsx_chip {scalar_t__ asic_code; struct ms_info ms_card; } ;

/* Variables and functions */
 int CLK_40 ; 
 int CLK_60 ; 
 int CLK_80 ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int ms_switch_clock (struct rtsx_chip*) ; 

__attribute__((used)) static inline int ms_auto_tune_clock(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;

	if (chip->asic_code) {
		if (ms_card->ms_clock > 30)
			ms_card->ms_clock -= 20;
	} else {
		if (ms_card->ms_clock == CLK_80)
			ms_card->ms_clock = CLK_60;
		else if (ms_card->ms_clock == CLK_60)
			ms_card->ms_clock = CLK_40;
	}

	retval = ms_switch_clock(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
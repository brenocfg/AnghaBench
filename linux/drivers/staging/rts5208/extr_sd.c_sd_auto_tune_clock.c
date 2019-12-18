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
struct sd_info {int sd_clock; } ;
struct rtsx_chip {scalar_t__ asic_code; struct sd_info sd_card; } ;

/* Variables and functions */
#define  CLK_100 133 
#define  CLK_120 132 
#define  CLK_150 131 
#define  CLK_200 130 
 int CLK_50 ; 
#define  CLK_60 129 
#define  CLK_80 128 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int sd_switch_clock (struct rtsx_chip*) ; 

__attribute__((used)) static inline int sd_auto_tune_clock(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	if (chip->asic_code) {
		if (sd_card->sd_clock > 30)
			sd_card->sd_clock -= 20;
	} else {
		switch (sd_card->sd_clock) {
		case CLK_200:
			sd_card->sd_clock = CLK_150;
			break;

		case CLK_150:
			sd_card->sd_clock = CLK_120;
			break;

		case CLK_120:
			sd_card->sd_clock = CLK_100;
			break;

		case CLK_100:
			sd_card->sd_clock = CLK_80;
			break;

		case CLK_80:
			sd_card->sd_clock = CLK_60;
			break;

		case CLK_60:
			sd_card->sd_clock = CLK_50;
			break;

		default:
			break;
		}
	}

	retval = sd_switch_clock(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
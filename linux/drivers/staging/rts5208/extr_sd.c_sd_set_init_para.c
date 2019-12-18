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
struct sd_info {int /*<<< orphan*/  sd_clock; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  sd_choose_proper_clock (struct rtsx_chip*) ; 
 int sd_set_sample_push_timing (struct rtsx_chip*) ; 
 int switch_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_set_init_para(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	retval = sd_set_sample_push_timing(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	sd_choose_proper_clock(chip);

	retval = switch_clock(chip, sd_card->sd_clock);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
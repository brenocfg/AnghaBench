#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ delay_write_flag; } ;
struct ms_info {int /*<<< orphan*/  raw_model_name; int /*<<< orphan*/  raw_sys_info; scalar_t__ pro_under_formatting; TYPE_1__ delay_write; } ;
struct rtsx_chip {int /*<<< orphan*/  card_wp; int /*<<< orphan*/  card_fail; int /*<<< orphan*/  card_ready; struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_CARD ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ms_free_l2p_tbl (struct rtsx_chip*) ; 
 int ms_power_off_card3v3 (struct rtsx_chip*) ; 

int release_ms_card(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;

#ifdef MS_DELAY_WRITE
	ms_card->delay_write.delay_write_flag = 0;
#endif
	ms_card->pro_under_formatting = 0;

	chip->card_ready &= ~MS_CARD;
	chip->card_fail &= ~MS_CARD;
	chip->card_wp &= ~MS_CARD;

	ms_free_l2p_tbl(chip);

	memset(ms_card->raw_sys_info, 0, 96);
#ifdef SUPPORT_PCGL_1P18
	memset(ms_card->raw_model_name, 0, 48);
#endif

	retval = ms_power_off_card3v3(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
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
struct sd_info {int sd_clock; scalar_t__ sd_erase_status; scalar_t__ sd_lock_status; scalar_t__ capacity; scalar_t__ sd_data_buf_ready; scalar_t__ seq_mode; scalar_t__ sd_type; } ;
struct rtsx_chip {size_t* card2lun; scalar_t__ sd_io; scalar_t__* capacity; scalar_t__ asic_code; struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STOP ; 
 int CLK_30 ; 
 int /*<<< orphan*/  REG_SD_CFG1 ; 
 size_t SD_CARD ; 
 int SD_CLR_ERR ; 
 int SD_STOP ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int sd_set_init_para (struct rtsx_chip*) ; 
 int select_card (struct rtsx_chip*,size_t) ; 

__attribute__((used)) static int sd_prepare_reset(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	if (chip->asic_code)
		sd_card->sd_clock = 29;
	else
		sd_card->sd_clock = CLK_30;

	sd_card->sd_type = 0;
	sd_card->seq_mode = 0;
	sd_card->sd_data_buf_ready = 0;
	sd_card->capacity = 0;

#ifdef SUPPORT_SD_LOCK
	sd_card->sd_lock_status = 0;
	sd_card->sd_erase_status = 0;
#endif

	chip->capacity[chip->card2lun[SD_CARD]] = 0;
	chip->sd_io = 0;

	retval = sd_set_init_para(chip);
	if (retval != STATUS_SUCCESS)
		return retval;

	retval = rtsx_write_register(chip, REG_SD_CFG1, 0xFF, 0x40);
	if (retval)
		return retval;

	retval = rtsx_write_register(chip, CARD_STOP, SD_STOP | SD_CLR_ERR,
				     SD_STOP | SD_CLR_ERR);
	if (retval)
		return retval;

	retval = select_card(chip, SD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
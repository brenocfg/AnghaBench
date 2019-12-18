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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_chip {int cur_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_SELECT ; 
 int MS_CARD ; 
 int /*<<< orphan*/  MS_MOD_SEL ; 
 int SD_CARD ; 
 int /*<<< orphan*/  SD_MOD_SEL ; 
 int SPI_CARD ; 
 int /*<<< orphan*/  SPI_MOD_SEL ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int XD_CARD ; 
 int /*<<< orphan*/  XD_MOD_SEL ; 
 int card_share_mode (struct rtsx_chip*,int) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int select_card(struct rtsx_chip *chip, int card)
{
	int retval;

	if (chip->cur_card != card) {
		u8 mod;

		if (card == SD_CARD)
			mod = SD_MOD_SEL;
		else if (card == MS_CARD)
			mod = MS_MOD_SEL;
		else if (card == XD_CARD)
			mod = XD_MOD_SEL;
		else if (card == SPI_CARD)
			mod = SPI_MOD_SEL;
		else
			return STATUS_FAIL;

		retval = rtsx_write_register(chip, CARD_SELECT, 0x07, mod);
		if (retval)
			return retval;
		chip->cur_card = card;

		retval =  card_share_mode(chip, card);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}
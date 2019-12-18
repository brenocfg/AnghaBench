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
typedef  int u32 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int MS_CARD ; 
 int MS_EXIST ; 
 int /*<<< orphan*/  RTSX_BIPR ; 
 int SD_CARD ; 
 int SD_EXIST ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int XD_CARD ; 
 int XD_EXIST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

int detect_card_cd(struct rtsx_chip *chip, int card)
{
	u32 card_cd, status;

	if (card == SD_CARD) {
		card_cd = SD_EXIST;
	} else if (card == MS_CARD) {
		card_cd = MS_EXIST;
	} else if (card == XD_CARD) {
		card_cd = XD_EXIST;
	} else {
		dev_dbg(rtsx_dev(chip), "Wrong card type: 0x%x\n", card);
		return STATUS_FAIL;
	}

	status = rtsx_readl(chip, RTSX_BIPR);
	if (!(status & card_cd))
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
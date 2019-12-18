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
typedef  int u8 ;
struct rtsx_chip {int /*<<< orphan*/  card_wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_INT ; 
 int INT_REG_CED ; 
 int INT_REG_CMDNK ; 
 int INT_REG_ERR ; 
 int /*<<< orphan*/  MS_CARD ; 
 int MS_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  MS_NO_CARD ; 
 int /*<<< orphan*/  NO_WAIT_INT ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int ms_read_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int ms_confirm_cpu_startup(struct rtsx_chip *chip)
{
	int retval, i, k;
	u8 val;

	/* Confirm CPU StartUp */
	k = 0;
	do {
		if (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) {
			ms_set_err_code(chip, MS_NO_CARD);
			return STATUS_FAIL;
		}

		for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
			retval = ms_read_bytes(chip, GET_INT, 1,
					       NO_WAIT_INT, &val, 1);
			if (retval == STATUS_SUCCESS)
				break;
		}
		if (i == MS_MAX_RETRY_COUNT)
			return STATUS_FAIL;

		if (k > 100)
			return STATUS_FAIL;

		k++;
		wait_timeout(100);
	} while (!(val & INT_REG_CED));

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_read_bytes(chip, GET_INT, 1, NO_WAIT_INT, &val, 1);
		if (retval == STATUS_SUCCESS)
			break;
	}
	if (i == MS_MAX_RETRY_COUNT)
		return STATUS_FAIL;

	if (val & INT_REG_ERR) {
		if (val & INT_REG_CMDNK)
			chip->card_wp |= (MS_CARD);
		else
			return STATUS_FAIL;
	}
	/* --  end confirm CPU startup */

	return STATUS_SUCCESS;
}
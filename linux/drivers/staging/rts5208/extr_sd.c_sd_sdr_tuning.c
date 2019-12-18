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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int sd_tuning_rx (struct rtsx_chip*) ; 
 int sd_tuning_tx (struct rtsx_chip*) ; 

__attribute__((used)) static int sd_sdr_tuning(struct rtsx_chip *chip)
{
	int retval;

	retval = sd_tuning_tx(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = sd_tuning_rx(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
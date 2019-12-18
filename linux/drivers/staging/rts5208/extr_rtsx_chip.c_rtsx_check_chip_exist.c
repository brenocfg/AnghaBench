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
 int rtsx_readl (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

int rtsx_check_chip_exist(struct rtsx_chip *chip)
{
	if (rtsx_readl(chip, 0) == 0xFFFFFFFF)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
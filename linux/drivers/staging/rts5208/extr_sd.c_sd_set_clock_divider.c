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
typedef  scalar_t__ u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SD_CFG1 ; 
 scalar_t__ SD_CLK_DIVIDE_0 ; 
 scalar_t__ SD_CLK_DIVIDE_128 ; 
 scalar_t__ SD_CLK_DIVIDE_256 ; 
 int STATUS_SUCCESS ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sd_set_clock_divider(struct rtsx_chip *chip, u8 clk_div)
{
	int retval;
	u8 mask = 0, val = 0;

	mask = 0x60;
	if (clk_div == SD_CLK_DIVIDE_0)
		val = 0x00;
	else if (clk_div == SD_CLK_DIVIDE_128)
		val = 0x40;
	else if (clk_div == SD_CLK_DIVIDE_256)
		val = 0x20;

	retval = rtsx_write_register(chip, REG_SD_CFG1, mask, val);
	if (retval)
		return retval;

	return STATUS_SUCCESS;
}
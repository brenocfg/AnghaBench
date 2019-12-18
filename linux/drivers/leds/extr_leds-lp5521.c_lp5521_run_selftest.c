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
struct lp55xx_platform_data {scalar_t__ clock_mode; } ;
struct lp55xx_chip {struct lp55xx_platform_data* pdata; } ;

/* Variables and functions */
 int EIO ; 
 int LP5521_EXT_CLK_USED ; 
 int /*<<< orphan*/  LP5521_REG_STATUS ; 
 scalar_t__ LP55XX_CLOCK_EXT ; 
 int lp55xx_read (struct lp55xx_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp5521_run_selftest(struct lp55xx_chip *chip, char *buf)
{
	struct lp55xx_platform_data *pdata = chip->pdata;
	int ret;
	u8 status;

	ret = lp55xx_read(chip, LP5521_REG_STATUS, &status);
	if (ret < 0)
		return ret;

	if (pdata->clock_mode != LP55XX_CLOCK_EXT)
		return 0;

	/* Check that ext clock is really in use if requested */
	if  ((status & LP5521_EXT_CLK_USED) == 0)
		return -EIO;

	return 0;
}
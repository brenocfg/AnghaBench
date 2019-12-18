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
struct tc_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int PLLEN ; 
 int PLLUPDATE ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_pllupdate(struct tc_data *tc, unsigned int pllctrl)
{
	int ret;

	ret = regmap_write(tc->regmap, pllctrl, PLLUPDATE | PLLEN);
	if (ret)
		return ret;

	/* Wait for PLL to lock: up to 2.09 ms, depending on refclk */
	usleep_range(3000, 6000);

	return 0;
}
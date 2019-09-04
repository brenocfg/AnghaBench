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

/* Variables and functions */
 int /*<<< orphan*/  FPGA_BKLREG ; 
 int /*<<< orphan*/  GPIO_PTS3 ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ap320_wvga_set_brightness(int brightness)
{
	if (brightness) {
		gpio_set_value(GPIO_PTS3, 0);
		__raw_writew(0x100, FPGA_BKLREG);
	} else {
		__raw_writew(0, FPGA_BKLREG);
		gpio_set_value(GPIO_PTS3, 1);
	}

	return 0;
}
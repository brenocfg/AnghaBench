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
struct rt1711h_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT1711H_RTCTRL13 ; 
 int rt1711h_write8 (struct rt1711h_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt1711h_sw_reset(struct rt1711h_chip *chip)
{
	int ret;

	ret = rt1711h_write8(chip, RT1711H_RTCTRL13, 0x01);
	if (ret < 0)
		return ret;

	usleep_range(1000, 2000);
	return 0;
}
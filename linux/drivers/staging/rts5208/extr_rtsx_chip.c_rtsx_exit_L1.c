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
 int /*<<< orphan*/  rtsx_write_config_byte (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 

void rtsx_exit_L1(struct rtsx_chip *chip)
{
	rtsx_write_config_byte(chip, 0x44, 0);
	rtsx_write_config_byte(chip, 0x45, 0);
}
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
 int /*<<< orphan*/  rtsx_write_phy_register (struct rtsx_chip*,int,int) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static void rtsx_calibration(struct rtsx_chip *chip)
{
	rtsx_write_phy_register(chip, 0x1B, 0x135E);
	wait_timeout(10);
	rtsx_write_phy_register(chip, 0x00, 0x0280);
	rtsx_write_phy_register(chip, 0x01, 0x7112);
	rtsx_write_phy_register(chip, 0x01, 0x7110);
	rtsx_write_phy_register(chip, 0x01, 0x7112);
	rtsx_write_phy_register(chip, 0x01, 0x7113);
	rtsx_write_phy_register(chip, 0x00, 0x0288);
}
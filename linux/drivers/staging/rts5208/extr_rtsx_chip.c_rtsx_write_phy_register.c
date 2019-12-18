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
typedef  int u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYADDR ; 
 int /*<<< orphan*/  PHYDATA0 ; 
 int /*<<< orphan*/  PHYDATA1 ; 
 int /*<<< orphan*/  PHYRWCTL ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 

int rtsx_write_phy_register(struct rtsx_chip *chip, u8 addr, u16 val)
{
	int retval;
	bool finished = false;
	int i;
	u8 tmp;

	retval = rtsx_write_register(chip, PHYDATA0, 0xFF, (u8)val);
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, PHYDATA1, 0xFF, (u8)(val >> 8));
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, PHYADDR, 0xFF, addr);
	if (retval)
		return retval;
	retval = rtsx_write_register(chip, PHYRWCTL, 0xFF, 0x81);
	if (retval)
		return retval;

	for (i = 0; i < 100000; i++) {
		retval = rtsx_read_register(chip, PHYRWCTL, &tmp);
		if (retval)
			return retval;
		if (!(tmp & 0x80)) {
			finished = true;
			break;
		}
	}

	if (!finished)
		return STATUS_FAIL;

	return STATUS_SUCCESS;
}
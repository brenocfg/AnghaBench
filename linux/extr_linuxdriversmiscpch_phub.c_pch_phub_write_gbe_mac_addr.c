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
typedef  int /*<<< orphan*/  u8 ;
struct pch_phub_reg {int ioh_type; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int pch_phub_gbe_serial_rom_conf (struct pch_phub_reg*) ; 
 int pch_phub_gbe_serial_rom_conf_mp (struct pch_phub_reg*) ; 
 int pch_phub_write_serial_rom_val (struct pch_phub_reg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_phub_write_gbe_mac_addr(struct pch_phub_reg *chip, u8 *data)
{
	int retval;
	int i;

	if ((chip->ioh_type == 1) || (chip->ioh_type == 5)) /* EG20T or ML7831*/
		retval = pch_phub_gbe_serial_rom_conf(chip);
	else	/* ML7223 */
		retval = pch_phub_gbe_serial_rom_conf_mp(chip);
	if (retval)
		return retval;

	for (i = 0; i < ETH_ALEN; i++) {
		retval = pch_phub_write_serial_rom_val(chip, i, data[i]);
		if (retval)
			return retval;
	}

	return retval;
}
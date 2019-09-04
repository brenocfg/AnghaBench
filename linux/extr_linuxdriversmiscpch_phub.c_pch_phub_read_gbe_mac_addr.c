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
struct pch_phub_reg {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  pch_phub_read_serial_rom_val (struct pch_phub_reg*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_phub_read_gbe_mac_addr(struct pch_phub_reg *chip, u8 *data)
{
	int i;
	for (i = 0; i < ETH_ALEN; i++)
		pch_phub_read_serial_rom_val(chip, i, &data[i]);
}
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
 int MLX5_EEPROM_HIGH_PAGE_LENGTH ; 
 int MLX5_EEPROM_PAGE_LENGTH ; 

__attribute__((used)) static int mlx5_eeprom_page(int offset)
{
	if (offset < MLX5_EEPROM_PAGE_LENGTH)
		/* Addresses between 0-255 - page 00 */
		return 0;

	/* Addresses between 256 - 639 belongs to pages 01, 02 and 03
	 * For example, offset = 400 belongs to page 02:
	 * 1 + ((400 - 256)/128) = 2
	 */
	return 1 + ((offset - MLX5_EEPROM_PAGE_LENGTH) /
		    MLX5_EEPROM_HIGH_PAGE_LENGTH);
}
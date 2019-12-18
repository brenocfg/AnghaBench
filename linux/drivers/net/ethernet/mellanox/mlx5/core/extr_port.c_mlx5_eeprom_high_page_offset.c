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

__attribute__((used)) static int mlx5_eeprom_high_page_offset(int page_num)
{
	if (!page_num) /* Page 0 always start from low page */
		return 0;

	/* High page */
	return page_num * MLX5_EEPROM_HIGH_PAGE_LENGTH;
}
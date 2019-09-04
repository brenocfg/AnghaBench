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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static int nand_id_has_period(u8 *id_data, int arrlen, int period)
{
	int i, j;
	for (i = 0; i < period; i++)
		for (j = i + period; j < arrlen; j += period)
			if (id_data[i] != id_data[j])
				return 0;
	return 1;
}
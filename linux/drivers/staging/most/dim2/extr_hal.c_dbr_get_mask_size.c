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
typedef  int u16 ;

/* Variables and functions */
 int DBR_BLOCK_SIZE ; 

__attribute__((used)) static int dbr_get_mask_size(u16 size)
{
	int i;

	for (i = 0; i < 6; i++)
		if (size <= (DBR_BLOCK_SIZE << i))
			return 1 << i;
	return 0;
}
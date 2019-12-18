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

__attribute__((used)) static bool edid_block_verify_crc(u8 *edid_block)
{
	u8 sum = 0;
	int i;

	for (i = 0; i < 128; i++)
		sum += edid_block[i];
	return sum == 0;
}
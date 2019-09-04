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
typedef  scalar_t__ uint8_t ;
struct fru_board_info_area {int area_len; } ;

/* Variables and functions */

int fru_bia_cksum_ok(struct fru_board_info_area *bia)
{
	uint8_t *ptr = (void *)bia;
	int i, sum;

	for (i = sum = 0; i < 8 * bia->area_len; i++)
		sum += ptr[i];
	return (sum & 0xff) == 0;
}
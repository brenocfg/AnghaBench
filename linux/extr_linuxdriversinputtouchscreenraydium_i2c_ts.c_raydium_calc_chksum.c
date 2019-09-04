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
typedef  size_t u16 ;

/* Variables and functions */

__attribute__((used)) static u16 raydium_calc_chksum(const u8 *buf, u16 len)
{
	u16 checksum = 0;
	u16 i;

	for (i = 0; i < len; i++)
		checksum += buf[i];

	return checksum;
}
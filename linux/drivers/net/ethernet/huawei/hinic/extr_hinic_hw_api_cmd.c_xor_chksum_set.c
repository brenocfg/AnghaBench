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

/* Variables and functions */

__attribute__((used)) static u8 xor_chksum_set(void *data)
{
	int idx;
	u8 *val, checksum = 0;

	val = data;

	for (idx = 0; idx < 7; idx++)
		checksum ^= val[idx];

	return checksum;
}
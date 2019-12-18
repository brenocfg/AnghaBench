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

__attribute__((used)) static u8 wilco_ec_checksum(const void *data, size_t size)
{
	u8 *data_bytes = (u8 *)data;
	u8 checksum = 0;
	size_t i;

	for (i = 0; i < size; i++)
		checksum += data_bytes[i];

	return checksum;
}
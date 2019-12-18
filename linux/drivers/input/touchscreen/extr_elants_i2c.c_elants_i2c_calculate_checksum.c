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
typedef  size_t u8 ;

/* Variables and functions */
 size_t FW_POS_CHECKSUM ; 

__attribute__((used)) static u8 elants_i2c_calculate_checksum(u8 *buf)
{
	u8 checksum = 0;
	u8 i;

	for (i = 0; i < FW_POS_CHECKSUM; i++)
		checksum += buf[i];

	return checksum;
}
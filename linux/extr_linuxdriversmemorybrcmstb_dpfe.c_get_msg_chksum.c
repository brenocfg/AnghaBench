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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int MSG_FIELD_MAX ; 

__attribute__((used)) static unsigned int get_msg_chksum(const u32 msg[])
{
	unsigned int sum = 0;
	unsigned int i;

	/* Don't include the last field in the checksum. */
	for (i = 0; i < MSG_FIELD_MAX - 1; i++)
		sum += msg[i];

	return sum;
}
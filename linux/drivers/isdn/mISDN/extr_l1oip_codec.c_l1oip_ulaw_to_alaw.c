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
 int /*<<< orphan*/ * ulaw_to_alaw ; 

int
l1oip_ulaw_to_alaw(u8 *data, int len, u8 *result)
{
	int i = 0;

	while (i < len) {
		*result++ = ulaw_to_alaw[*data++];
		i++;
	}

	return len;
}
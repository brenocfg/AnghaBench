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

/* Variables and functions */

__attribute__((used)) static bool pm_checkpacket(unsigned char *packet)
{
	int total = 0;
	int i;

	for (i = 0; i < 5; i++)
		total += packet[i];

	return packet[5] == (unsigned char)~(total & 0xff);
}
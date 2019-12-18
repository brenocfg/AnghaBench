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

void scsi_sanitize_inquiry_string(unsigned char *s, int len)
{
	int terminated = 0;

	for (; len > 0; (--len, ++s)) {
		if (*s == 0)
			terminated = 1;
		if (terminated || *s < 0x20 || *s > 0x7e)
			*s = ' ';
	}
}
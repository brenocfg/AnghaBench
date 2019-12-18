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

__attribute__((used)) static void
ch_check_voltag(char *tag)
{
	int i;

	for (i = 0; i < 32; i++) {
		/* restrict to ascii */
		if (tag[i] >= 0x7f || tag[i] < 0x20)
			tag[i] = ' ';
		/* don't allow search wildcards */
		if (tag[i] == '?' ||
		    tag[i] == '*')
			tag[i] = ' ';
	}
}
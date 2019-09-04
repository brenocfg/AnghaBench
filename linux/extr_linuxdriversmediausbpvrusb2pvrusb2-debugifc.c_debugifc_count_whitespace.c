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

__attribute__((used)) static unsigned int debugifc_count_whitespace(const char *buf,
					      unsigned int count)
{
	unsigned int scnt;
	char ch;

	for (scnt = 0; scnt < count; scnt++) {
		ch = buf[scnt];
		if (ch == ' ') continue;
		if (ch == '\t') continue;
		if (ch == '\n') continue;
		break;
	}
	return scnt;
}
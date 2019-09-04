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
 int prom_nbputchar (char const*) ; 

void prom_console_write_buf(const char *buf, int len)
{
	while (len) {
		int n = prom_nbputchar(buf);
		if (n < 0)
			continue;
		len--;
		buf++;
	}
}
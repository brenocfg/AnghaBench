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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int DCC_STATUS_TX ; 
 int __dcc_getstatus () ; 
 int /*<<< orphan*/  __dcc_putchar (char const) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static int hvc_dcc_put_chars(uint32_t vt, const char *buf, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		while (__dcc_getstatus() & DCC_STATUS_TX)
			cpu_relax();

		__dcc_putchar(buf[i]);
	}

	return count;
}
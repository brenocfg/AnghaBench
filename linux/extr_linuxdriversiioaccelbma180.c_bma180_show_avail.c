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
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int const) ; 

__attribute__((used)) static ssize_t bma180_show_avail(char *buf, const int *vals, unsigned int n,
				 bool micros)
{
	size_t len = 0;
	int i;

	for (i = 0; i < n; i++) {
		if (!vals[i])
			continue;
		len += scnprintf(buf + len, PAGE_SIZE - len,
			micros ? "0.%06d " : "%d ", vals[i]);
	}
	buf[len - 1] = '\n';

	return len;
}
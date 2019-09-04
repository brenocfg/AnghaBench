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
 int /*<<< orphan*/  DLE ; 

__attribute__((used)) static inline int
dle_count(unsigned char *buf, int len)
{
	int count = 0;

	while (len--)
		if (*buf++ == DLE)
			count++;
	return count;
}
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

__attribute__((used)) static int mdc800_isReady (char *ch)
{
	int i=0;
	while (i<8)
	{
		if (ch [i] != (char)0xbb)
			return 0;
		i++;
	}
	return 1;
}
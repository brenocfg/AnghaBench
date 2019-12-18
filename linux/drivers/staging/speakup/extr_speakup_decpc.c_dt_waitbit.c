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
 int dt_getstatus () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dt_waitbit(int bit)
{
	int timeout = 100;

	while (--timeout > 0) {
		if ((dt_getstatus() & bit) == bit)
			return 1;
		udelay(50);
	}
	return 0;
}
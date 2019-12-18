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
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 

__attribute__((used)) static inline void clcdfb_sleep(unsigned int ms)
{
	if (in_atomic()) {
		mdelay(ms);
	} else {
		msleep(ms);
	}
}
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
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline void lp5562_wait_opmode_done(void)
{
	/* operation mode change needs to be longer than 153 us */
	usleep_range(200, 300);
}
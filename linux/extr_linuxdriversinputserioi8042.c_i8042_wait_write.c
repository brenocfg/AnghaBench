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
 int I8042_CTL_TIMEOUT ; 
 int I8042_STR_IBF ; 
 int i8042_read_status () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int i8042_wait_write(void)
{
	int i = 0;

	while ((i8042_read_status() & I8042_STR_IBF) && (i < I8042_CTL_TIMEOUT)) {
		udelay(50);
		i++;
	}
	return -(i == I8042_CTL_TIMEOUT);
}
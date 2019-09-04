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
 scalar_t__ HPET_COUNTER ; 
 int /*<<< orphan*/  hpet_write (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpet_reset_counter(void)
{
	hpet_write(HPET_COUNTER, 0);
	hpet_write(HPET_COUNTER + 4, 0);
}
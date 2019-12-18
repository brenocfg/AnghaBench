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
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  mdelay (unsigned long) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 

__attribute__((used)) static void maybe_msleep(unsigned long ms)
{
	/* During early boot, IRQs are disabled, use mdelay */
	if (irqs_disabled())
		mdelay(ms);
	else
		msleep(ms);
}
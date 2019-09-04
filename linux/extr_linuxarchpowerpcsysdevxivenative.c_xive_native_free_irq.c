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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_free_irq (int /*<<< orphan*/ ) ; 

void xive_native_free_irq(u32 irq)
{
	for (;;) {
		s64 rc = opal_xive_free_irq(irq);
		if (rc != OPAL_BUSY)
			break;
		msleep(OPAL_BUSY_DELAY_MS);
	}
}
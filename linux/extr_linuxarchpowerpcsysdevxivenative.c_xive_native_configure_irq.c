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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_set_irq_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int xive_native_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
{
	s64 rc;

	for (;;) {
		rc = opal_xive_set_irq_config(hw_irq, target, prio, sw_irq);
		if (rc != OPAL_BUSY)
			break;
		msleep(OPAL_BUSY_DELAY_MS);
	}
	return rc == 0 ? 0 : -ENXIO;
}
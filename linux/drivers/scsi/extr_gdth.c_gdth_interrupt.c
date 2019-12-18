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
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  gdth_ha_str ;

/* Variables and functions */
 int /*<<< orphan*/  __gdth_interrupt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gdth_interrupt(int irq, void *dev_id)
{
	gdth_ha_str *ha = dev_id;

	return __gdth_interrupt(ha, false, NULL);
}
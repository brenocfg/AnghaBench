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
typedef  enum ams_irq { ____Placeholder_ams_irq } ams_irq ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_FREEFALL ; 
 int AMS_IRQ_FREEFALL ; 
 int AMS_IRQ_SHOCK ; 
 int /*<<< orphan*/  AMS_SHOCK ; 
 int /*<<< orphan*/  ams_i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ams_i2c_clear_irq(enum ams_irq reg)
{
	if (reg & AMS_IRQ_FREEFALL)
		ams_i2c_write(AMS_FREEFALL, 0);

	if (reg & AMS_IRQ_SHOCK)
		ams_i2c_write(AMS_SHOCK, 0);
}
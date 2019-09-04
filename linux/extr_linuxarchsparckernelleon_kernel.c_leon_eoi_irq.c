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
struct irq_data {scalar_t__ chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEON3_BYPASS_STORE_PA (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long LEON_DO_ACK_HW ; 
 int /*<<< orphan*/  LEON_IACK ; 

__attribute__((used)) static void leon_eoi_irq(struct irq_data *data)
{
	unsigned long mask = (unsigned long)data->chip_data;

	if (mask & LEON_DO_ACK_HW)
		LEON3_BYPASS_STORE_PA(LEON_IACK, mask & ~LEON_DO_ACK_HW);
}
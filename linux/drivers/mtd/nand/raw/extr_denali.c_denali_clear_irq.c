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
struct denali_controller {scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ INTR_STATUS (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void denali_clear_irq(struct denali_controller *denali,
			     int bank, u32 irq_status)
{
	/* write one to clear bits */
	iowrite32(irq_status, denali->reg + INTR_STATUS(bank));
}
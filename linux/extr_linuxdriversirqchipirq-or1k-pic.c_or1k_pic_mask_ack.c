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
struct irq_data {unsigned long hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_PICMR ; 
 int /*<<< orphan*/  SPR_PICSR ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void or1k_pic_mask_ack(struct irq_data *data)
{
	mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(1UL << data->hwirq));
	mtspr(SPR_PICSR, (1UL << data->hwirq));
}
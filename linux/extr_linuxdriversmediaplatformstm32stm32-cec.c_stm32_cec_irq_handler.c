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
struct stm32_cec {int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ALL_RX_IT ; 
 int ALL_TX_IT ; 
 int /*<<< orphan*/  CEC_ISR ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t stm32_cec_irq_handler(int irq, void *arg)
{
	struct stm32_cec *cec = arg;

	regmap_read(cec->regmap, CEC_ISR, &cec->irq_status);

	regmap_update_bits(cec->regmap, CEC_ISR,
			   ALL_TX_IT | ALL_RX_IT,
			   ALL_TX_IT | ALL_RX_IT);

	return IRQ_WAKE_THREAD;
}
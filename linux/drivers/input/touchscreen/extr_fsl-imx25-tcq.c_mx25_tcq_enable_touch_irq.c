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
struct mx25_tcq_priv {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MX25_ADCQ_CR ; 
 int /*<<< orphan*/  MX25_ADCQ_CR_PDMSK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mx25_tcq_enable_touch_irq(struct mx25_tcq_priv *priv)
{
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_PDMSK, 0);
}
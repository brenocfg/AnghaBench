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
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ HI655X_ANA_IRQM_BASE ; 
 int HI655X_IRQ_ARRAY ; 
 int /*<<< orphan*/  HI655X_IRQ_CLR ; 
 scalar_t__ HI655X_IRQ_STAT_BASE ; 
 int HI655X_STRIDE ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hi655x_local_irq_clear(struct regmap *map)
{
	int i;

	regmap_write(map, HI655X_ANA_IRQM_BASE, HI655X_IRQ_CLR);
	for (i = 0; i < HI655X_IRQ_ARRAY; i++) {
		regmap_write(map, HI655X_IRQ_STAT_BASE + i * HI655X_STRIDE,
			     HI655X_IRQ_CLR);
	}
}
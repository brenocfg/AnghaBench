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
struct allegro_dev {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AL5_ITC_CPU_IRQ_CLR ; 
 int /*<<< orphan*/  AL5_ITC_CPU_IRQ_STA ; 
 unsigned int AL5_ITC_CPU_IRQ_STA_TRIGGERED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t allegro_hardirq(int irq, void *data)
{
	struct allegro_dev *dev = data;
	unsigned int status;

	regmap_read(dev->regmap, AL5_ITC_CPU_IRQ_STA, &status);
	if (!(status & AL5_ITC_CPU_IRQ_STA_TRIGGERED))
		return IRQ_NONE;

	regmap_write(dev->regmap, AL5_ITC_CPU_IRQ_CLR, status);

	return IRQ_WAKE_THREAD;
}
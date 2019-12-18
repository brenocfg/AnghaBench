#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ dev; } ;
struct sii902x {TYPE_1__ bridge; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int SII902X_HOTPLUG_EVENT ; 
 int /*<<< orphan*/  SII902X_INT_STATUS ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t sii902x_interrupt(int irq, void *data)
{
	struct sii902x *sii902x = data;
	unsigned int status = 0;

	mutex_lock(&sii902x->mutex);

	regmap_read(sii902x->regmap, SII902X_INT_STATUS, &status);
	regmap_write(sii902x->regmap, SII902X_INT_STATUS, status);

	mutex_unlock(&sii902x->mutex);

	if ((status & SII902X_HOTPLUG_EVENT) && sii902x->bridge.dev)
		drm_helper_hpd_irq_event(sii902x->bridge.dev);

	return IRQ_HANDLED;
}
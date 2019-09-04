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
struct anx78xx {int /*<<< orphan*/  lock; scalar_t__ powered; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int anx78xx_enable_interrupts (struct anx78xx*) ; 
 int /*<<< orphan*/  anx78xx_poweron (struct anx78xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t anx78xx_hpd_threaded_handler(int irq, void *data)
{
	struct anx78xx *anx78xx = data;
	int err;

	if (anx78xx->powered)
		return IRQ_HANDLED;

	mutex_lock(&anx78xx->lock);

	/* Cable is pulled, power on the chip */
	anx78xx_poweron(anx78xx);

	err = anx78xx_enable_interrupts(anx78xx);
	if (err)
		DRM_ERROR("Failed to enable interrupts: %d\n", err);

	mutex_unlock(&anx78xx->lock);

	return IRQ_HANDLED;
}
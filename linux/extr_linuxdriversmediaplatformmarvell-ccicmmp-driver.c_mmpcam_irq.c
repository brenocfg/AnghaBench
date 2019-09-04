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
struct mcam_camera {int /*<<< orphan*/  dev_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 int /*<<< orphan*/  REG_IRQSTAT ; 
 unsigned int mcam_reg_read (struct mcam_camera*,int /*<<< orphan*/ ) ; 
 unsigned int mccic_irq (struct mcam_camera*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mmpcam_irq(int irq, void *data)
{
	struct mcam_camera *mcam = data;
	unsigned int irqs, handled;

	spin_lock(&mcam->dev_lock);
	irqs = mcam_reg_read(mcam, REG_IRQSTAT);
	handled = mccic_irq(mcam, irqs);
	spin_unlock(&mcam->dev_lock);
	return IRQ_RETVAL(handled);
}
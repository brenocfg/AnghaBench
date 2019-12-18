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
typedef  int u8 ;
struct ocores_i2c {int flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OCI2C_STATUS ; 
 int OCI2C_STAT_BUSY ; 
 int OCI2C_STAT_IF ; 
 int OCORES_FLAG_BROKEN_IRQ ; 
 int oc_getreg (struct ocores_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocores_process (struct ocores_i2c*,int) ; 

__attribute__((used)) static irqreturn_t ocores_isr(int irq, void *dev_id)
{
	struct ocores_i2c *i2c = dev_id;
	u8 stat = oc_getreg(i2c, OCI2C_STATUS);

	if (i2c->flags & OCORES_FLAG_BROKEN_IRQ) {
		if ((stat & OCI2C_STAT_IF) && !(stat & OCI2C_STAT_BUSY))
			return IRQ_NONE;
	} else if (!(stat & OCI2C_STAT_IF)) {
		return IRQ_NONE;
	}
	ocores_process(i2c, stat);

	return IRQ_HANDLED;
}
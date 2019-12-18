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
typedef  int u16 ;
struct mtk_i2c {int irq_stat; int ignore_restart_irq; int /*<<< orphan*/  msg_complete; scalar_t__ auto_restart; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int I2C_RS_MUL_CNFG ; 
 int I2C_RS_MUL_TRIG ; 
 int I2C_RS_TRANSFER ; 
 int I2C_TRANSAC_COMP ; 
 int I2C_TRANSAC_START ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OFFSET_INTR_STAT ; 
 int /*<<< orphan*/  OFFSET_START ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mtk_i2c_readw (struct mtk_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_i2c_writew (struct mtk_i2c*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mtk_i2c_irq(int irqno, void *dev_id)
{
	struct mtk_i2c *i2c = dev_id;
	u16 restart_flag = 0;
	u16 intr_stat;

	if (i2c->auto_restart)
		restart_flag = I2C_RS_TRANSFER;

	intr_stat = mtk_i2c_readw(i2c, OFFSET_INTR_STAT);
	mtk_i2c_writew(i2c, intr_stat, OFFSET_INTR_STAT);

	/*
	 * when occurs ack error, i2c controller generate two interrupts
	 * first is the ack error interrupt, then the complete interrupt
	 * i2c->irq_stat need keep the two interrupt value.
	 */
	i2c->irq_stat |= intr_stat;

	if (i2c->ignore_restart_irq && (i2c->irq_stat & restart_flag)) {
		i2c->ignore_restart_irq = false;
		i2c->irq_stat = 0;
		mtk_i2c_writew(i2c, I2C_RS_MUL_CNFG | I2C_RS_MUL_TRIG |
				    I2C_TRANSAC_START, OFFSET_START);
	} else {
		if (i2c->irq_stat & (I2C_TRANSAC_COMP | restart_flag))
			complete(&i2c->msg_complete);
	}

	return IRQ_HANDLED;
}
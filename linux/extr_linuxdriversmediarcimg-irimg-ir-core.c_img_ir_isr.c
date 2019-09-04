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
typedef  int u32 ;
struct img_ir_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_IRQ_CLEAR ; 
 int IMG_IR_IRQ_DATA2_VALID ; 
 int IMG_IR_IRQ_DATA_MATCH ; 
 int IMG_IR_IRQ_DATA_VALID ; 
 int IMG_IR_IRQ_EDGE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 int /*<<< orphan*/  IMG_IR_IRQ_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ img_ir_hw_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_ir_isr_hw (struct img_ir_priv*,int) ; 
 int /*<<< orphan*/  img_ir_isr_raw (struct img_ir_priv*,int) ; 
 scalar_t__ img_ir_raw_enabled (int /*<<< orphan*/ *) ; 
 int img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t img_ir_isr(int irq, void *dev_id)
{
	struct img_ir_priv *priv = dev_id;
	u32 irq_status;

	spin_lock(&priv->lock);
	/* we have to clear irqs before reading */
	irq_status = img_ir_read(priv, IMG_IR_IRQ_STATUS);
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, irq_status);

	/* don't handle valid data irqs if we're only interested in matches */
	irq_status &= img_ir_read(priv, IMG_IR_IRQ_ENABLE);

	/* hand off edge interrupts to raw decode handler */
	if (irq_status & IMG_IR_IRQ_EDGE && img_ir_raw_enabled(&priv->raw))
		img_ir_isr_raw(priv, irq_status);

	/* hand off hardware match interrupts to hardware decode handler */
	if (irq_status & (IMG_IR_IRQ_DATA_MATCH |
			  IMG_IR_IRQ_DATA_VALID |
			  IMG_IR_IRQ_DATA2_VALID) &&
	    img_ir_hw_enabled(&priv->hw))
		img_ir_isr_hw(priv, irq_status);

	spin_unlock(&priv->lock);
	return IRQ_HANDLED;
}
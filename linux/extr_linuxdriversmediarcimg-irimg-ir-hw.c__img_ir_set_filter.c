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
struct img_ir_priv_hw {int /*<<< orphan*/  flags; struct img_ir_filter* filters; } ;
struct img_ir_priv {struct img_ir_priv_hw hw; } ;
struct img_ir_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_F_FILTER ; 
 int /*<<< orphan*/  IMG_IR_IRQ_CLEAR ; 
 int IMG_IR_IRQ_DATA2_VALID ; 
 int IMG_IR_IRQ_DATA_MATCH ; 
 int IMG_IR_IRQ_DATA_VALID ; 
 int /*<<< orphan*/  IMG_IR_IRQ_ENABLE ; 
 size_t RC_FILTER_NORMAL ; 
 int img_ir_read (struct img_ir_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  img_ir_write_filter (struct img_ir_priv*,struct img_ir_filter*) ; 

__attribute__((used)) static void _img_ir_set_filter(struct img_ir_priv *priv,
			       struct img_ir_filter *filter)
{
	struct img_ir_priv_hw *hw = &priv->hw;
	u32 irq_en, irq_on;

	irq_en = img_ir_read(priv, IMG_IR_IRQ_ENABLE);
	if (filter) {
		/* Only use the match interrupt */
		hw->filters[RC_FILTER_NORMAL] = *filter;
		hw->flags |= IMG_IR_F_FILTER;
		irq_on = IMG_IR_IRQ_DATA_MATCH;
		irq_en &= ~(IMG_IR_IRQ_DATA_VALID | IMG_IR_IRQ_DATA2_VALID);
	} else {
		/* Only use the valid interrupt */
		hw->flags &= ~IMG_IR_F_FILTER;
		irq_en &= ~IMG_IR_IRQ_DATA_MATCH;
		irq_on = IMG_IR_IRQ_DATA_VALID | IMG_IR_IRQ_DATA2_VALID;
	}
	irq_en |= irq_on;

	img_ir_write_filter(priv, filter);
	/* clear any interrupts we're enabling so we don't handle old ones */
	img_ir_write(priv, IMG_IR_IRQ_CLEAR, irq_on);
	img_ir_write(priv, IMG_IR_IRQ_ENABLE, irq_en);
}
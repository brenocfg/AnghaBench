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
typedef  int u32 ;
struct aspeed_lpc_snoop {int /*<<< orphan*/ * chan; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HICR6 ; 
 int HICR6_STR_SNP0W ; 
 int HICR6_STR_SNP1W ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SNPWDR ; 
 int SNPWDR_CH0_MASK ; 
 int SNPWDR_CH0_SHIFT ; 
 int SNPWDR_CH1_MASK ; 
 int SNPWDR_CH1_SHIFT ; 
 int /*<<< orphan*/  put_fifo_with_discard (int /*<<< orphan*/ *,int) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t aspeed_lpc_snoop_irq(int irq, void *arg)
{
	struct aspeed_lpc_snoop *lpc_snoop = arg;
	u32 reg, data;

	if (regmap_read(lpc_snoop->regmap, HICR6, &reg))
		return IRQ_NONE;

	/* Check if one of the snoop channels is interrupting */
	reg &= (HICR6_STR_SNP0W | HICR6_STR_SNP1W);
	if (!reg)
		return IRQ_NONE;

	/* Ack pending IRQs */
	regmap_write(lpc_snoop->regmap, HICR6, reg);

	/* Read and save most recent snoop'ed data byte to FIFO */
	regmap_read(lpc_snoop->regmap, SNPWDR, &data);

	if (reg & HICR6_STR_SNP0W) {
		u8 val = (data & SNPWDR_CH0_MASK) >> SNPWDR_CH0_SHIFT;

		put_fifo_with_discard(&lpc_snoop->chan[0], val);
	}
	if (reg & HICR6_STR_SNP1W) {
		u8 val = (data & SNPWDR_CH1_MASK) >> SNPWDR_CH1_SHIFT;

		put_fifo_with_discard(&lpc_snoop->chan[1], val);
	}

	return IRQ_HANDLED;
}
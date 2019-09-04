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
typedef  int u8 ;
struct stmpe_variant_info {unsigned int id_mask; unsigned int id_val; int /*<<< orphan*/  name; } ;
struct stmpe {scalar_t__ irq; int /*<<< orphan*/ * regs; TYPE_1__* pdata; int /*<<< orphan*/  dev; struct stmpe_variant_info* variant; } ;
struct TYPE_2__ {unsigned int irq_trigger; int autosleep_timeout; scalar_t__ autosleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 unsigned int IRQF_TRIGGER_FALLING ; 
 unsigned int IRQF_TRIGGER_HIGH ; 
 unsigned int IRQF_TRIGGER_RISING ; 
 unsigned int STMPE1600_ID ; 
 unsigned int STMPE801_ID ; 
 int STMPE_ICR_LSB_EDGE ; 
 int STMPE_ICR_LSB_GIM ; 
 int STMPE_ICR_LSB_HIGH ; 
 size_t STMPE_IDX_CHIP_ID ; 
 size_t STMPE_IDX_ICR_LSB ; 
 int STMPE_SYS_CTRL_INT_EN ; 
 int STMPE_SYS_CTRL_INT_HI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int stmpe_autosleep (struct stmpe*,int) ; 
 int stmpe_block_read (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stmpe_disable (struct stmpe*,int /*<<< orphan*/ ) ; 
 int stmpe_reg_write (struct stmpe*,int /*<<< orphan*/ ,int) ; 
 int stmpe_reset (struct stmpe*) ; 

__attribute__((used)) static int stmpe_chip_init(struct stmpe *stmpe)
{
	unsigned int irq_trigger = stmpe->pdata->irq_trigger;
	int autosleep_timeout = stmpe->pdata->autosleep_timeout;
	struct stmpe_variant_info *variant = stmpe->variant;
	u8 icr = 0;
	unsigned int id;
	u8 data[2];
	int ret;

	ret = stmpe_block_read(stmpe, stmpe->regs[STMPE_IDX_CHIP_ID],
			       ARRAY_SIZE(data), data);
	if (ret < 0)
		return ret;

	id = (data[0] << 8) | data[1];
	if ((id & variant->id_mask) != variant->id_val) {
		dev_err(stmpe->dev, "unknown chip id: %#x\n", id);
		return -EINVAL;
	}

	dev_info(stmpe->dev, "%s detected, chip id: %#x\n", variant->name, id);

	/* Disable all modules -- subdrivers should enable what they need. */
	ret = stmpe_disable(stmpe, ~0);
	if (ret)
		return ret;

	ret =  stmpe_reset(stmpe);
	if (ret < 0)
		return ret;

	if (stmpe->irq >= 0) {
		if (id == STMPE801_ID || id == STMPE1600_ID)
			icr = STMPE_SYS_CTRL_INT_EN;
		else
			icr = STMPE_ICR_LSB_GIM;

		/* STMPE801 and STMPE1600 don't support Edge interrupts */
		if (id != STMPE801_ID && id != STMPE1600_ID) {
			if (irq_trigger == IRQF_TRIGGER_FALLING ||
					irq_trigger == IRQF_TRIGGER_RISING)
				icr |= STMPE_ICR_LSB_EDGE;
		}

		if (irq_trigger == IRQF_TRIGGER_RISING ||
				irq_trigger == IRQF_TRIGGER_HIGH) {
			if (id == STMPE801_ID || id == STMPE1600_ID)
				icr |= STMPE_SYS_CTRL_INT_HI;
			else
				icr |= STMPE_ICR_LSB_HIGH;
		}
	}

	if (stmpe->pdata->autosleep) {
		ret = stmpe_autosleep(stmpe, autosleep_timeout);
		if (ret)
			return ret;
	}

	return stmpe_reg_write(stmpe, stmpe->regs[STMPE_IDX_ICR_LSB], icr);
}
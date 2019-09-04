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
typedef  int uint8_t ;
struct rc5t583_irq_data {size_t mask_reg_index; int int_en_bit; size_t master_bit; int grp_index; } ;
struct rc5t583 {int* group_irq_en; scalar_t__ irq_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RC5T583_INTC_INTMON ; 
 int RC5T583_MAX_INTERRUPT_MASK_REGS ; 
 int RC5T583_MAX_IRQS ; 
 int RTC_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_nested_irq (scalar_t__) ; 
 int /*<<< orphan*/ * irq_clr_add ; 
 int /*<<< orphan*/ * irq_mon_add ; 
 int* main_int_type ; 
 struct rc5t583_irq_data* rc5t583_irqs ; 
 int rc5t583_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int rc5t583_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t rc5t583_irq(int irq, void *data)
{
	struct rc5t583 *rc5t583 = data;
	uint8_t int_sts[RC5T583_MAX_INTERRUPT_MASK_REGS];
	uint8_t master_int = 0;
	int i;
	int ret;
	unsigned int rtc_int_sts = 0;

	/* Clear the status */
	for (i = 0; i < RC5T583_MAX_INTERRUPT_MASK_REGS; i++)
		int_sts[i] = 0;

	ret  = rc5t583_read(rc5t583->dev, RC5T583_INTC_INTMON, &master_int);
	if (ret < 0) {
		dev_err(rc5t583->dev,
			"Error in reading reg 0x%02x error: %d\n",
			RC5T583_INTC_INTMON, ret);
		return IRQ_HANDLED;
	}

	for (i = 0; i < RC5T583_MAX_INTERRUPT_MASK_REGS; ++i) {
		if (!(master_int & main_int_type[i]))
			continue;

		ret = rc5t583_read(rc5t583->dev, irq_mon_add[i], &int_sts[i]);
		if (ret < 0) {
			dev_warn(rc5t583->dev,
				"Error in reading reg 0x%02x error: %d\n",
				irq_mon_add[i], ret);
			int_sts[i] = 0;
			continue;
		}

		if (main_int_type[i] & RTC_INT) {
			rtc_int_sts = 0;
			if (int_sts[i] & 0x1)
				rtc_int_sts |= BIT(6);
			if (int_sts[i] & 0x2)
				rtc_int_sts |= BIT(7);
			if (int_sts[i] & 0x4)
				rtc_int_sts |= BIT(0);
			if (int_sts[i] & 0x8)
				rtc_int_sts |= BIT(5);
		}

		ret = rc5t583_write(rc5t583->dev, irq_clr_add[i],
				~int_sts[i]);
		if (ret < 0)
			dev_warn(rc5t583->dev,
				"Error in reading reg 0x%02x error: %d\n",
				irq_clr_add[i], ret);

		if (main_int_type[i] & RTC_INT)
			int_sts[i] = rtc_int_sts;
	}

	/* Merge gpio interrupts for rising and falling case*/
	int_sts[7] |= int_sts[8];

	/* Call interrupt handler if enabled */
	for (i = 0; i < RC5T583_MAX_IRQS; ++i) {
		const struct rc5t583_irq_data *data = &rc5t583_irqs[i];
		if ((int_sts[data->mask_reg_index] & (1 << data->int_en_bit)) &&
			(rc5t583->group_irq_en[data->master_bit] &
					(1 << data->grp_index)))
			handle_nested_irq(rc5t583->irq_base + i);
	}

	return IRQ_HANDLED;
}
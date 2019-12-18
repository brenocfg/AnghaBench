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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct stmpe_adc {scalar_t__ channel; int /*<<< orphan*/  completion; scalar_t__ value; int /*<<< orphan*/  stmpe; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int STMPE_ADC_CH (scalar_t__) ; 
 scalar_t__ STMPE_ADC_LAST_NR ; 
 int /*<<< orphan*/  STMPE_REG_ADC_DATA_CH (scalar_t__) ; 
 int /*<<< orphan*/  STMPE_REG_ADC_INT_STA ; 
 int /*<<< orphan*/  STMPE_REG_TEMP_DATA ; 
 scalar_t__ STMPE_TEMP_CHANNEL ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmpe_block_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int stmpe_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t stmpe_adc_isr(int irq, void *dev_id)
{
	struct stmpe_adc *info = (struct stmpe_adc *)dev_id;
	u16 data;

	if (info->channel <= STMPE_ADC_LAST_NR) {
		int int_sta;

		int_sta = stmpe_reg_read(info->stmpe, STMPE_REG_ADC_INT_STA);

		/* Is the interrupt relevant */
		if (!(int_sta & STMPE_ADC_CH(info->channel)))
			return IRQ_NONE;

		/* Read value */
		stmpe_block_read(info->stmpe,
			STMPE_REG_ADC_DATA_CH(info->channel), 2, (u8 *) &data);

		stmpe_reg_write(info->stmpe, STMPE_REG_ADC_INT_STA, int_sta);
	} else if (info->channel == STMPE_TEMP_CHANNEL) {
		/* Read value */
		stmpe_block_read(info->stmpe, STMPE_REG_TEMP_DATA, 2,
				(u8 *) &data);
	} else {
		return IRQ_NONE;
	}

	info->value = (u32) be16_to_cpu(data);
	complete(&info->completion);

	return IRQ_HANDLED;
}
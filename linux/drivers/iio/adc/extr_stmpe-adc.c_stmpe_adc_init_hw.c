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
struct stmpe_adc {struct stmpe* stmpe; } ;
struct stmpe {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_BLOCK_ADC ; 
 scalar_t__ STMPE_REG_TEMP_TH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int stmpe811_adc_common_init (struct stmpe*) ; 
 int /*<<< orphan*/  stmpe_disable (struct stmpe*,int /*<<< orphan*/ ) ; 
 int stmpe_enable (struct stmpe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_reg_write (struct stmpe*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_adc_init_hw(struct stmpe_adc *adc)
{
	int ret;
	struct stmpe *stmpe = adc->stmpe;

	ret = stmpe_enable(stmpe, STMPE_BLOCK_ADC);
	if (ret) {
		dev_err(stmpe->dev, "Could not enable clock for ADC\n");
		return ret;
	}

	ret = stmpe811_adc_common_init(stmpe);
	if (ret) {
		stmpe_disable(stmpe, STMPE_BLOCK_ADC);
		return ret;
	}

	/* use temp irq for each conversion completion */
	stmpe_reg_write(stmpe, STMPE_REG_TEMP_TH, 0);
	stmpe_reg_write(stmpe, STMPE_REG_TEMP_TH + 1, 0);

	return 0;
}
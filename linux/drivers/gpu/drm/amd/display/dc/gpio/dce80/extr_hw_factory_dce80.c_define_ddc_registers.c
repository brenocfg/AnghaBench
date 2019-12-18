#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct hw_gpio_pin {int id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * regs; } ;
struct hw_ddc {int /*<<< orphan*/ * masks; int /*<<< orphan*/ * shifts; TYPE_1__ base; TYPE_2__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  GPIO_ID_DDC_CLOCK 129 
#define  GPIO_ID_DDC_DATA 128 
 struct hw_ddc* HW_DDC_FROM_BASE (struct hw_gpio_pin*) ; 
 TYPE_2__* ddc_clk_regs ; 
 TYPE_2__* ddc_data_regs ; 
 int /*<<< orphan*/  ddc_mask ; 
 int /*<<< orphan*/  ddc_shift ; 

__attribute__((used)) static void define_ddc_registers(
		struct hw_gpio_pin *pin,
		uint32_t en)
{
	struct hw_ddc *ddc = HW_DDC_FROM_BASE(pin);

	switch (pin->id) {
	case GPIO_ID_DDC_DATA:
		ddc->regs = &ddc_data_regs[en];
		ddc->base.regs = &ddc_data_regs[en].gpio;
		break;
	case GPIO_ID_DDC_CLOCK:
		ddc->regs = &ddc_clk_regs[en];
		ddc->base.regs = &ddc_clk_regs[en].gpio;
		break;
	default:
		ASSERT_CRITICAL(false);
		return;
	}

	ddc->shifts = &ddc_shift;
	ddc->masks = &ddc_mask;

}
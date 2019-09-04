#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void** int_any; void** int_polarity; void** int_type; void** int_en; void** dirm; void** datamsw; void** datalsw; } ;
struct zynq_gpio {scalar_t__ base_addr; TYPE_2__ context; TYPE_1__* p_data; } ;
struct TYPE_3__ {unsigned int max_bank; } ;

/* Variables and functions */
 scalar_t__ ZYNQ_GPIO_DATA_LSW_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_DATA_MSW_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_DIRM_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_INTANY_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_INTMASK_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_INTPOL_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_INTTYPE_OFFSET (unsigned int) ; 
 void* readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void zynq_gpio_save_context(struct zynq_gpio *gpio)
{
	unsigned int bank_num;

	for (bank_num = 0; bank_num < gpio->p_data->max_bank; bank_num++) {
		gpio->context.datalsw[bank_num] =
				readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_DATA_LSW_OFFSET(bank_num));
		gpio->context.datamsw[bank_num] =
				readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_DATA_MSW_OFFSET(bank_num));
		gpio->context.dirm[bank_num] = readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_DIRM_OFFSET(bank_num));
		gpio->context.int_en[bank_num] = readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTMASK_OFFSET(bank_num));
		gpio->context.int_type[bank_num] =
				readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTTYPE_OFFSET(bank_num));
		gpio->context.int_polarity[bank_num] =
				readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTPOL_OFFSET(bank_num));
		gpio->context.int_any[bank_num] =
				readl_relaxed(gpio->base_addr +
				ZYNQ_GPIO_INTANY_OFFSET(bank_num));
	}
}
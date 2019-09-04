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
struct stm32_exti_host_data {struct stm32_exti_host_data* chips_data; int /*<<< orphan*/  base; struct stm32_exti_drv_data const* drv_data; } ;
struct stm32_exti_drv_data {int /*<<< orphan*/  bank_nr; } ;
struct stm32_exti_chip_data {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct stm32_exti_host_data* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stm32_exti_host_data*) ; 
 struct stm32_exti_host_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*) ; 
 struct stm32_exti_host_data* stm32_host_data ; 

__attribute__((used)) static struct
stm32_exti_host_data *stm32_exti_host_init(const struct stm32_exti_drv_data *dd,
					   struct device_node *node)
{
	struct stm32_exti_host_data *host_data;

	host_data = kzalloc(sizeof(*host_data), GFP_KERNEL);
	if (!host_data)
		return NULL;

	host_data->drv_data = dd;
	host_data->chips_data = kcalloc(dd->bank_nr,
					sizeof(struct stm32_exti_chip_data),
					GFP_KERNEL);
	if (!host_data->chips_data)
		goto free_host_data;

	host_data->base = of_iomap(node, 0);
	if (!host_data->base) {
		pr_err("%pOF: Unable to map registers\n", node);
		goto free_chips_data;
	}

	stm32_host_data = host_data;

	return host_data;

free_chips_data:
	kfree(host_data->chips_data);
free_host_data:
	kfree(host_data);

	return NULL;
}
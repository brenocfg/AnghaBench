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
struct rmi_function_handler {int /*<<< orphan*/  attention; } ;
struct rmi_function {int num_of_irqs; int /*<<< orphan*/  dev; int /*<<< orphan*/ * irq; scalar_t__ irq_pos; int /*<<< orphan*/  irq_mask; TYPE_1__* rmi_dev; } ;
struct rmi_driver_data {int /*<<< orphan*/  irqdomain; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rmi_function*) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int /*<<< orphan*/ ,struct rmi_function*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rmi_irq_chip ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_create_function_irq(struct rmi_function *fn,
				   struct rmi_function_handler *handler)
{
	struct rmi_driver_data *drvdata = dev_get_drvdata(&fn->rmi_dev->dev);
	int i, error;

	for (i = 0; i < fn->num_of_irqs; i++) {
		set_bit(fn->irq_pos + i, fn->irq_mask);

		fn->irq[i] = irq_create_mapping(drvdata->irqdomain,
						fn->irq_pos + i);

		irq_set_chip_data(fn->irq[i], fn);
		irq_set_chip_and_handler(fn->irq[i], &rmi_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thread(fn->irq[i], 1);

		error = devm_request_threaded_irq(&fn->dev, fn->irq[i], NULL,
					handler->attention, IRQF_ONESHOT,
					dev_name(&fn->dev), fn);
		if (error) {
			dev_err(&fn->dev, "Error %d registering IRQ\n", error);
			return error;
		}
	}

	return 0;
}
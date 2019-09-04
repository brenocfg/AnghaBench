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
struct platform_device {int dummy; } ;
struct da9055_onkey {int /*<<< orphan*/  input; int /*<<< orphan*/  work; TYPE_1__* da9055; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct da9055_onkey*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct da9055_onkey* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da9055_onkey_remove(struct platform_device *pdev)
{
	struct da9055_onkey *onkey = platform_get_drvdata(pdev);
	int irq = platform_get_irq_byname(pdev, "ONKEY");

	irq = regmap_irq_get_virq(onkey->da9055->irq_data, irq);
	free_irq(irq, onkey);
	cancel_delayed_work_sync(&onkey->work);
	input_unregister_device(onkey->input);

	return 0;
}
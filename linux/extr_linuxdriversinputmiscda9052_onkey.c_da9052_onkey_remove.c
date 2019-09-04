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
struct platform_device {int dummy; } ;
struct da9052_onkey {int /*<<< orphan*/  input; int /*<<< orphan*/  work; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_NONKEY ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da9052_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da9052_onkey*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct da9052_onkey*) ; 
 struct da9052_onkey* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int da9052_onkey_remove(struct platform_device *pdev)
{
	struct da9052_onkey *onkey = platform_get_drvdata(pdev);

	da9052_free_irq(onkey->da9052, DA9052_IRQ_NONKEY, onkey);
	cancel_delayed_work_sync(&onkey->work);

	input_unregister_device(onkey->input);
	kfree(onkey);

	return 0;
}
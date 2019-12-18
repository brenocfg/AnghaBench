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
struct mx25_tsadc {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mx25_tsadc* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx25_tsadc_remove(struct platform_device *pdev)
{
	struct mx25_tsadc *tsadc = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);

	if (irq) {
		irq_set_chained_handler_and_data(irq, NULL, NULL);
		irq_domain_remove(tsadc->domain);
	}

	return 0;
}
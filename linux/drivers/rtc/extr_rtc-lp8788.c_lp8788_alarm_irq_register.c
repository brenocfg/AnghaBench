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
struct resource {int start; int end; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lp8788_rtc {scalar_t__ alarm; int /*<<< orphan*/  irq; struct lp8788* lp; } ;
struct lp8788 {struct irq_domain* irqdm; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ LP8788_ALARM_1 ; 
 int /*<<< orphan*/  LP8788_ALM_IRQ ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lp8788_rtc*) ; 
 int /*<<< orphan*/  irq_create_mapping (struct irq_domain*,int) ; 
 int /*<<< orphan*/  lp8788_alarm_irq_handler ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8788_alarm_irq_register(struct platform_device *pdev,
				struct lp8788_rtc *rtc)
{
	struct resource *r;
	struct lp8788 *lp = rtc->lp;
	struct irq_domain *irqdm = lp->irqdm;
	int irq;

	rtc->irq = 0;

	/* even the alarm IRQ number is not specified, rtc time should work */
	r = platform_get_resource_byname(pdev, IORESOURCE_IRQ, LP8788_ALM_IRQ);
	if (!r)
		return 0;

	if (rtc->alarm == LP8788_ALARM_1)
		irq = r->start;
	else
		irq = r->end;

	rtc->irq = irq_create_mapping(irqdm, irq);

	return devm_request_threaded_irq(&pdev->dev, rtc->irq, NULL,
				lp8788_alarm_irq_handler,
				0, LP8788_ALM_IRQ, rtc);
}
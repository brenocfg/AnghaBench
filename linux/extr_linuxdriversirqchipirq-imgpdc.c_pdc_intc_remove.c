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
struct pdc_intc_priv {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct pdc_intc_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pdc_intc_remove(struct platform_device *pdev)
{
	struct pdc_intc_priv *priv = platform_get_drvdata(pdev);

	irq_domain_remove(priv->domain);
	return 0;
}
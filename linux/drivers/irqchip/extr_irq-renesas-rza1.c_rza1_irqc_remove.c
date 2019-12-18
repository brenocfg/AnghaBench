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
struct rza1_irqc_priv {int /*<<< orphan*/  irq_domain; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct rza1_irqc_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rza1_irqc_remove(struct platform_device *pdev)
{
	struct rza1_irqc_priv *priv = platform_get_drvdata(pdev);

	irq_domain_remove(priv->irq_domain);
	return 0;
}
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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mc13xxx_buttons_platform_data {int b3on_flags; int b2on_flags; int b1on_flags; } ;
struct mc13783_pwrb {int /*<<< orphan*/  pwr; int /*<<< orphan*/  mc13783; } ;

/* Variables and functions */
 int MC13783_BUTTON_ENABLE ; 
 int /*<<< orphan*/  MC13783_IRQ_ONOFD1 ; 
 int /*<<< orphan*/  MC13783_IRQ_ONOFD2 ; 
 int /*<<< orphan*/  MC13783_IRQ_ONOFD3 ; 
 struct mc13xxx_buttons_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mc13783_pwrb*) ; 
 int /*<<< orphan*/  mc13xxx_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mc13783_pwrb*) ; 
 int /*<<< orphan*/  mc13xxx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc13xxx_unlock (int /*<<< orphan*/ ) ; 
 struct mc13783_pwrb* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mc13783_pwrbutton_remove(struct platform_device *pdev)
{
	struct mc13783_pwrb *priv = platform_get_drvdata(pdev);
	const struct mc13xxx_buttons_platform_data *pdata;

	pdata = dev_get_platdata(&pdev->dev);

	mc13xxx_lock(priv->mc13783);

	if (pdata->b3on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_free(priv->mc13783, MC13783_IRQ_ONOFD3, priv);
	if (pdata->b2on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_free(priv->mc13783, MC13783_IRQ_ONOFD2, priv);
	if (pdata->b1on_flags & MC13783_BUTTON_ENABLE)
		mc13xxx_irq_free(priv->mc13783, MC13783_IRQ_ONOFD1, priv);

	mc13xxx_unlock(priv->mc13783);

	input_unregister_device(priv->pwr);
	kfree(priv);

	return 0;
}
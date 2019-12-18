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
struct am35x_glue {int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  clk; int /*<<< orphan*/  phy; int /*<<< orphan*/  musb; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct am35x_glue*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct am35x_glue* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am35x_remove(struct platform_device *pdev)
{
	struct am35x_glue	*glue = platform_get_drvdata(pdev);

	platform_device_unregister(glue->musb);
	usb_phy_generic_unregister(glue->phy);
	clk_disable(glue->clk);
	clk_disable(glue->phy_clk);
	clk_put(glue->clk);
	clk_put(glue->phy_clk);
	kfree(glue);

	return 0;
}
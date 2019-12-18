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
struct tahvo_usb {int /*<<< orphan*/  ick; int /*<<< orphan*/  phy; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct tahvo_usb*) ; 
 struct tahvo_usb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tahvo_usb_remove(struct platform_device *pdev)
{
	struct tahvo_usb *tu = platform_get_drvdata(pdev);

	free_irq(tu->irq, tu);
	usb_remove_phy(&tu->phy);
	if (!IS_ERR(tu->ick))
		clk_disable(tu->ick);

	return 0;
}
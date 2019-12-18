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
struct musb {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  dev_timer; TYPE_1__* controller; } ;
struct da8xx_glue {int /*<<< orphan*/  clk; int /*<<< orphan*/  phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct da8xx_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_musb_exit(struct musb *musb)
{
	struct da8xx_glue *glue = dev_get_drvdata(musb->controller->parent);

	del_timer_sync(&musb->dev_timer);

	phy_power_off(glue->phy);
	phy_exit(glue->phy);
	clk_disable_unprepare(glue->clk);

	usb_put_phy(musb->xceiv);

	return 0;
}
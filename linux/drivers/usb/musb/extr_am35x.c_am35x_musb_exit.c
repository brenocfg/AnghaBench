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
struct omap_musb_board_data {int /*<<< orphan*/  (* set_phy_power ) (int /*<<< orphan*/ ) ;} ;
struct musb_hdrc_platform_data {struct omap_musb_board_data* board_data; } ;
struct musb {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  dev_timer; struct device* controller; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct musb_hdrc_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am35x_musb_exit(struct musb *musb)
{
	struct device *dev = musb->controller;
	struct musb_hdrc_platform_data *plat = dev_get_platdata(dev);
	struct omap_musb_board_data *data = plat->board_data;

	del_timer_sync(&musb->dev_timer);

	/* Shutdown the on-chip PHY and its PLL. */
	if (data->set_phy_power)
		data->set_phy_power(0);

	usb_put_phy(musb->xceiv);

	return 0;
}
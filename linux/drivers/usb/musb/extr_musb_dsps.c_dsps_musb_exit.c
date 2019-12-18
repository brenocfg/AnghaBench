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
struct musb {int /*<<< orphan*/  phy; int /*<<< orphan*/  dev_timer; struct device* controller; } ;
struct dsps_glue {int /*<<< orphan*/  dbgfs_root; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct dsps_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsps_musb_exit(struct musb *musb)
{
	struct device *dev = musb->controller;
	struct dsps_glue *glue = dev_get_drvdata(dev->parent);

	del_timer_sync(&musb->dev_timer);
	phy_power_off(musb->phy);
	phy_exit(musb->phy);
	debugfs_remove_recursive(glue->dbgfs_root);

	return 0;
}
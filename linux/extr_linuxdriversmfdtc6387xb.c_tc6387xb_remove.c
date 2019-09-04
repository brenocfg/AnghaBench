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
struct tc6387xb {int /*<<< orphan*/  clk32k; int /*<<< orphan*/  rscr; int /*<<< orphan*/  scr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc6387xb*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct tc6387xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tc6387xb_remove(struct platform_device *dev)
{
	struct tc6387xb *tc6387xb = platform_get_drvdata(dev);

	mfd_remove_devices(&dev->dev);
	iounmap(tc6387xb->scr);
	release_resource(&tc6387xb->rscr);
	clk_disable_unprepare(tc6387xb->clk32k);
	clk_put(tc6387xb->clk32k);
	kfree(tc6387xb);

	return 0;
}
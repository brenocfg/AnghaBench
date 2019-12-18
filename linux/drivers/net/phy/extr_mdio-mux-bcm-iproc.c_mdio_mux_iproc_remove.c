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
struct iproc_mdiomux_desc {int /*<<< orphan*/  core_clk; int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  mux_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_mux_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct iproc_mdiomux_desc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mdio_mux_iproc_remove(struct platform_device *pdev)
{
	struct iproc_mdiomux_desc *md = platform_get_drvdata(pdev);

	mdio_mux_uninit(md->mux_handle);
	mdiobus_unregister(md->mii_bus);
	clk_disable_unprepare(md->core_clk);

	return 0;
}
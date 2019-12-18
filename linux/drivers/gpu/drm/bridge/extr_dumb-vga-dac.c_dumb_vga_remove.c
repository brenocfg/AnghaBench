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
struct dumb_vga {scalar_t__ ddc; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (scalar_t__) ; 
 struct dumb_vga* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dumb_vga_remove(struct platform_device *pdev)
{
	struct dumb_vga *vga = platform_get_drvdata(pdev);

	drm_bridge_remove(&vga->bridge);

	if (vga->ddc)
		i2c_put_adapter(vga->ddc);

	return 0;
}
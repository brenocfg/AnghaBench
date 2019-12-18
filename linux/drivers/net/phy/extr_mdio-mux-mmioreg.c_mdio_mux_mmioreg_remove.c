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
struct mdio_mux_mmioreg_state {int /*<<< orphan*/  mux_handle; } ;

/* Variables and functions */
 struct mdio_mux_mmioreg_state* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdio_mux_uninit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_mux_mmioreg_remove(struct platform_device *pdev)
{
	struct mdio_mux_mmioreg_state *s = dev_get_platdata(&pdev->dev);

	mdio_mux_uninit(s->mux_handle);

	return 0;
}
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
struct tegra_xusb_port {int /*<<< orphan*/  index; int /*<<< orphan*/  padctl; } ;
struct tegra_xusb_lane {int dummy; } ;

/* Variables and functions */
 struct tegra_xusb_lane* tegra_xusb_find_lane (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tegra_xusb_lane *
tegra124_usb2_port_map(struct tegra_xusb_port *port)
{
	return tegra_xusb_find_lane(port->padctl, "usb2", port->index);
}
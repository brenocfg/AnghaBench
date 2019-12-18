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
struct tegra_xusb_usb2_port {int dummy; } ;
struct tegra_xusb_port {int dummy; } ;
struct tegra_xusb_padctl {int dummy; } ;

/* Variables and functions */
 struct tegra_xusb_port* tegra_xusb_find_port (struct tegra_xusb_padctl*,char*,unsigned int) ; 
 struct tegra_xusb_usb2_port* to_usb2_port (struct tegra_xusb_port*) ; 

struct tegra_xusb_usb2_port *
tegra_xusb_find_usb2_port(struct tegra_xusb_padctl *padctl, unsigned int index)
{
	struct tegra_xusb_port *port;

	port = tegra_xusb_find_port(padctl, "usb2", index);
	if (port)
		return to_usb2_port(port);

	return NULL;
}
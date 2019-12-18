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
struct tty_port {int dummy; } ;
struct tty_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* tty_port_register_device_attr (struct tty_port*,struct tty_driver*,unsigned int,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct device *tty_port_register_device(struct tty_port *port,
		struct tty_driver *driver, unsigned index,
		struct device *device)
{
	return tty_port_register_device_attr(port, driver, index, device, NULL, NULL);
}
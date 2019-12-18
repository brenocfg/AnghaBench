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
struct parport {int /*<<< orphan*/  bus_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ *) ; 
 struct parport* to_parport_dev (struct device*) ; 

struct parport *parport_get_port(struct parport *port)
{
	struct device *dev = get_device(&port->bus_dev);

	return to_parport_dev(dev);
}
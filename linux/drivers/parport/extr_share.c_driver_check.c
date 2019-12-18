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
struct parport_driver {int /*<<< orphan*/  (* match_port ) (struct parport*) ;} ;
struct parport {int dummy; } ;
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct parport*) ; 
 struct parport_driver* to_parport_driver (struct device_driver*) ; 

__attribute__((used)) static int driver_check(struct device_driver *dev_drv, void *_port)
{
	struct parport *port = _port;
	struct parport_driver *drv = to_parport_driver(dev_drv);

	if (drv->match_port)
		drv->match_port(port);
	return 0;
}
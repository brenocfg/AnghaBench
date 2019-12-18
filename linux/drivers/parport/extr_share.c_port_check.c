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
struct parport_driver {int /*<<< orphan*/  (* match_port ) (int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_parport (struct device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_parport_dev (struct device*) ; 

__attribute__((used)) static int port_check(struct device *dev, void *dev_drv)
{
	struct parport_driver *drv = dev_drv;

	/* only send ports, do not send other devices connected to bus */
	if (is_parport(dev))
		drv->match_port(to_parport_dev(dev));
	return 0;
}
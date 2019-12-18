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
struct xenbus_driver {int /*<<< orphan*/  read_otherend_details; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_frontend_details ; 
 int /*<<< orphan*/  xenbus_backend ; 
 int xenbus_register_driver_common (struct xenbus_driver*,int /*<<< orphan*/ *,struct module*,char const*) ; 

int __xenbus_register_backend(struct xenbus_driver *drv, struct module *owner,
			      const char *mod_name)
{
	drv->read_otherend_details = read_frontend_details;

	return xenbus_register_driver_common(drv, &xenbus_backend,
					     owner, mod_name);
}
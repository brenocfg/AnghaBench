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
struct parport_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct parport_driver*) ; 
 int /*<<< orphan*/  parport_unregister_driver (struct parport_driver*) ; 

void pi_unregister_driver(void *_drv)
{
	struct parport_driver *drv = _drv;

	parport_unregister_driver(drv);
	kfree(drv);
}
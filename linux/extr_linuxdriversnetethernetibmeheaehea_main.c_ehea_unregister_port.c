#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ehea_port {TYPE_1__ ofdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_log_port_id ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static void ehea_unregister_port(struct ehea_port *port)
{
	device_remove_file(&port->ofdev.dev, &dev_attr_log_port_id);
	of_device_unregister(&port->ofdev);
}
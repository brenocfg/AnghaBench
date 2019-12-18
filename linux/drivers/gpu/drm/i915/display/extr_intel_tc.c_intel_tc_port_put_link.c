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
struct intel_digital_port {int /*<<< orphan*/  tc_lock; int /*<<< orphan*/  tc_link_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_tc_port_put_link(struct intel_digital_port *dig_port)
{
	mutex_lock(&dig_port->tc_lock);
	dig_port->tc_link_refcount--;
	mutex_unlock(&dig_port->tc_lock);
}
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
struct intel_digital_port {int /*<<< orphan*/  tc_mode; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_tc_port_lock (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_tc_port_unlock (struct intel_digital_port*) ; 
 int tc_port_live_status_mask (struct intel_digital_port*) ; 

bool intel_tc_port_connected(struct intel_digital_port *dig_port)
{
	bool is_connected;

	intel_tc_port_lock(dig_port);
	is_connected = tc_port_live_status_mask(dig_port) &
		       BIT(dig_port->tc_mode);
	intel_tc_port_unlock(dig_port);

	return is_connected;
}
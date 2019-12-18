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
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_tc_port_lock (struct intel_digital_port*,int) ; 

void intel_tc_port_lock(struct intel_digital_port *dig_port)
{
	__intel_tc_port_lock(dig_port, 1);
}
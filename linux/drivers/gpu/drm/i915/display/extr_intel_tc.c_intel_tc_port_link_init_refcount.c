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
struct intel_digital_port {int tc_link_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void
intel_tc_port_link_init_refcount(struct intel_digital_port *dig_port,
				 int refcount)
{
	WARN_ON(dig_port->tc_link_refcount);
	dig_port->tc_link_refcount = refcount;
}
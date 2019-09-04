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
struct port {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_SLAVE_NOTIFY_LATER ; 
 int /*<<< orphan*/  bond_set_slave_inactive_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __disable_port(struct port *port)
{
	bond_set_slave_inactive_flags(port->slave, BOND_SLAVE_NOTIFY_LATER);
}
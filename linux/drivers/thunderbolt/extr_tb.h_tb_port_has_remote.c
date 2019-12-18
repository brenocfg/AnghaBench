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
struct tb_port {scalar_t__ link_nr; scalar_t__ dual_link_port; int /*<<< orphan*/  remote; } ;

/* Variables and functions */
 scalar_t__ tb_is_upstream_port (struct tb_port const*) ; 

__attribute__((used)) static inline bool tb_port_has_remote(const struct tb_port *port)
{
	if (tb_is_upstream_port(port))
		return false;
	if (!port->remote)
		return false;
	if (port->dual_link_port && port->link_nr)
		return false;

	return true;
}
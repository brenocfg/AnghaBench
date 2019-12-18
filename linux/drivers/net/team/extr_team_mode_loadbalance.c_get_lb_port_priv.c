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
struct team_port {int /*<<< orphan*/  mode_priv; } ;
struct lb_port_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct lb_port_priv *get_lb_port_priv(struct team_port *port)
{
	return (struct lb_port_priv *) &port->mode_priv;
}
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
struct tb_port {struct tb_port const* dual_link_port; int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 struct tb_port* tb_upstream_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tb_is_upstream_port(const struct tb_port *port)
{
	const struct tb_port *upstream_port = tb_upstream_port(port->sw);
	return port == upstream_port || port->dual_link_port == upstream_port;
}
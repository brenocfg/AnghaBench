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
struct ehea_port {int num_def_qps; int /*<<< orphan*/  qp_eq; int /*<<< orphan*/ * port_res; } ;

/* Variables and functions */
 int ehea_clean_portres (struct ehea_port*,int /*<<< orphan*/ *) ; 
 int ehea_destroy_eq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_clean_all_portres(struct ehea_port *port)
{
	int ret = 0;
	int i;

	for (i = 0; i < port->num_def_qps; i++)
		ret |= ehea_clean_portres(port, &port->port_res[i]);

	ret |= ehea_destroy_eq(port->qp_eq);

	return ret;
}
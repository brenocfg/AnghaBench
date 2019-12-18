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
typedef  int /*<<< orphan*/  u16 ;
struct rvt_ibport {int /*<<< orphan*/ * pkey_table; } ;
struct rvt_dev_info {struct rvt_ibport** ports; } ;

/* Variables and functions */

int rvt_init_port(struct rvt_dev_info *rdi, struct rvt_ibport *port,
		  int port_index, u16 *pkey_table)
{

	rdi->ports[port_index] = port;
	rdi->ports[port_index]->pkey_table = pkey_table;

	return 0;
}
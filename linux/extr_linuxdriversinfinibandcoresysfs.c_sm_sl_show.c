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
struct port_attribute {int dummy; } ;
struct ib_port_attr {int sm_sl; } ;
struct ib_port {int /*<<< orphan*/  port_num; int /*<<< orphan*/  ibdev; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ib_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t sm_sl_show(struct ib_port *p, struct port_attribute *unused,
			  char *buf)
{
	struct ib_port_attr attr;
	ssize_t ret;

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	if (ret)
		return ret;

	return sprintf(buf, "%d\n", attr.sm_sl);
}
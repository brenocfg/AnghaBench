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
struct ib_port_attr {size_t state; } ;
struct ib_port {int /*<<< orphan*/  port_num; int /*<<< orphan*/  ibdev; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
#define  IB_PORT_ACTIVE 133 
#define  IB_PORT_ACTIVE_DEFER 132 
#define  IB_PORT_ARMED 131 
#define  IB_PORT_DOWN 130 
#define  IB_PORT_INIT 129 
#define  IB_PORT_NOP 128 
 scalar_t__ ib_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ sprintf (char*,char*,size_t,char const*) ; 

__attribute__((used)) static ssize_t state_show(struct ib_port *p, struct port_attribute *unused,
			  char *buf)
{
	struct ib_port_attr attr;
	ssize_t ret;

	static const char *state_name[] = {
		[IB_PORT_NOP]		= "NOP",
		[IB_PORT_DOWN]		= "DOWN",
		[IB_PORT_INIT]		= "INIT",
		[IB_PORT_ARMED]		= "ARMED",
		[IB_PORT_ACTIVE]	= "ACTIVE",
		[IB_PORT_ACTIVE_DEFER]	= "ACTIVE_DEFER"
	};

	ret = ib_query_port(p->ibdev, p->port_num, &attr);
	if (ret)
		return ret;

	return sprintf(buf, "%d: %s\n", attr.state,
		       attr.state >= 0 && attr.state < ARRAY_SIZE(state_name) ?
		       state_name[attr.state] : "UNKNOWN");
}
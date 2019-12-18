#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ida {int dummy; } ;
struct TYPE_2__ {int max_in_hop_id; int max_out_hop_id; } ;
struct tb_port {struct ida out_hopids; TYPE_1__ config; struct ida in_hopids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TB_PATH_MIN_HOPID ; 
 int ida_simple_get (struct ida*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_port_alloc_hopid(struct tb_port *port, bool in, int min_hopid,
			       int max_hopid)
{
	int port_max_hopid;
	struct ida *ida;

	if (in) {
		port_max_hopid = port->config.max_in_hop_id;
		ida = &port->in_hopids;
	} else {
		port_max_hopid = port->config.max_out_hop_id;
		ida = &port->out_hopids;
	}

	/* HopIDs 0-7 are reserved */
	if (min_hopid < TB_PATH_MIN_HOPID)
		min_hopid = TB_PATH_MIN_HOPID;

	if (max_hopid < 0 || max_hopid > port_max_hopid)
		max_hopid = port_max_hopid;

	return ida_simple_get(ida, min_hopid, max_hopid + 1, GFP_KERNEL);
}
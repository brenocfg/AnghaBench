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
struct mvpp2_port {int /*<<< orphan*/  priv; int /*<<< orphan*/  id; } ;
struct mvpp2_cls_flow_entry {int dummy; } ;
struct mvpp2_cls_flow {int flow_type; int /*<<< orphan*/  flow_id; } ;

/* Variables and functions */
 int MVPP2_N_FLOWS ; 
 int MVPP2_PORT_FLOW_HASH_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvpp2_cls_flow* mvpp2_cls_flow_get (int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_read (int /*<<< orphan*/ ,int,struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_flow_get_hek_fields (struct mvpp2_cls_flow_entry*) ; 

__attribute__((used)) static u16 mvpp2_port_rss_hash_opts_get(struct mvpp2_port *port, int flow_type)
{
	struct mvpp2_cls_flow_entry fe;
	struct mvpp2_cls_flow *flow;
	int i, flow_index;
	u16 hash_opts = 0;

	for (i = 0; i < MVPP2_N_FLOWS; i++) {
		flow = mvpp2_cls_flow_get(i);
		if (!flow)
			return 0;

		if (flow->flow_type != flow_type)
			continue;

		flow_index = MVPP2_PORT_FLOW_HASH_ENTRY(port->id,
							flow->flow_id);

		mvpp2_cls_flow_read(port->priv, flow_index, &fe);

		hash_opts |= mvpp2_flow_get_hek_fields(&fe);
	}

	return hash_opts;
}
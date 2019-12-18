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
struct mvpp2_cls_flow_entry {int index; } ;
struct mvpp2_cls_flow {int /*<<< orphan*/  flow_id; } ;
struct mvpp2 {int dummy; } ;
typedef  int /*<<< orphan*/  fe ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MVPP22_CLS_ENGINE_C2 ; 
 int /*<<< orphan*/  MVPP22_CLS_ENGINE_C3HA ; 
 int /*<<< orphan*/  MVPP22_CLS_LU_TYPE_ALL ; 
 int /*<<< orphan*/  MVPP2_CLS_FLT_C2_RSS_ENTRY (int /*<<< orphan*/ ) ; 
 int MVPP2_CLS_FLT_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_CLS_FLT_HASH_ENTRY (int,int /*<<< orphan*/ ) ; 
 int MVPP2_CLS_FLT_LAST (int /*<<< orphan*/ ) ; 
 int MVPP2_MAX_PORTS ; 
 int /*<<< orphan*/  memset (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_eng_set (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_last_set (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_lu_type_set (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_port_add (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_port_id_sel (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_pri_set (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_read (struct mvpp2*,int /*<<< orphan*/ ,struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_write (struct mvpp2*,struct mvpp2_cls_flow_entry*) ; 

__attribute__((used)) static void mvpp2_cls_flow_init(struct mvpp2 *priv,
				const struct mvpp2_cls_flow *flow)
{
	struct mvpp2_cls_flow_entry fe;
	int i, pri = 0;

	/* Assign default values to all entries in the flow */
	for (i = MVPP2_CLS_FLT_FIRST(flow->flow_id);
	     i <= MVPP2_CLS_FLT_LAST(flow->flow_id); i++) {
		memset(&fe, 0, sizeof(fe));
		fe.index = i;
		mvpp2_cls_flow_pri_set(&fe, pri++);

		if (i == MVPP2_CLS_FLT_LAST(flow->flow_id))
			mvpp2_cls_flow_last_set(&fe, 1);

		mvpp2_cls_flow_write(priv, &fe);
	}

	/* RSS config C2 lookup */
	mvpp2_cls_flow_read(priv, MVPP2_CLS_FLT_C2_RSS_ENTRY(flow->flow_id),
			    &fe);

	mvpp2_cls_flow_eng_set(&fe, MVPP22_CLS_ENGINE_C2);
	mvpp2_cls_flow_port_id_sel(&fe, true);
	mvpp2_cls_flow_lu_type_set(&fe, MVPP22_CLS_LU_TYPE_ALL);

	/* Add all ports */
	for (i = 0; i < MVPP2_MAX_PORTS; i++)
		mvpp2_cls_flow_port_add(&fe, BIT(i));

	mvpp2_cls_flow_write(priv, &fe);

	/* C3Hx lookups */
	for (i = 0; i < MVPP2_MAX_PORTS; i++) {
		mvpp2_cls_flow_read(priv,
				    MVPP2_CLS_FLT_HASH_ENTRY(i, flow->flow_id),
				    &fe);

		/* Set a default engine. Will be overwritten when setting the
		 * real HEK parameters
		 */
		mvpp2_cls_flow_eng_set(&fe, MVPP22_CLS_ENGINE_C3HA);
		mvpp2_cls_flow_port_id_sel(&fe, true);
		mvpp2_cls_flow_port_add(&fe, BIT(i));

		mvpp2_cls_flow_write(priv, &fe);
	}
}
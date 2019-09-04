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
struct mvpp2_cls_flow_entry {int /*<<< orphan*/  index; } ;
struct mvpp2_cls_flow {int /*<<< orphan*/  flow_id; } ;
struct mvpp2 {int dummy; } ;
typedef  int /*<<< orphan*/  fe ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MVPP22_CLS_ENGINE_C2 ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_SEQ_FIRST1 ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_SEQ_LAST ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_SEQ_MIDDLE ; 
 int /*<<< orphan*/  MVPP2_FLOW_C2_ENTRY (int /*<<< orphan*/ ) ; 
 int MVPP2_MAX_PORTS ; 
 int /*<<< orphan*/  MVPP2_PORT_FLOW_HASH_ENTRY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_eng_set (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_last_set (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_port_add (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_port_id_sel (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_pri_set (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_seq_set (struct mvpp2_cls_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_write (struct mvpp2*,struct mvpp2_cls_flow_entry*) ; 

__attribute__((used)) static void mvpp2_cls_flow_init(struct mvpp2 *priv, struct mvpp2_cls_flow *flow)
{
	struct mvpp2_cls_flow_entry fe;
	int i;

	/* C2 lookup */
	memset(&fe, 0, sizeof(fe));
	fe.index = MVPP2_FLOW_C2_ENTRY(flow->flow_id);

	mvpp2_cls_flow_eng_set(&fe, MVPP22_CLS_ENGINE_C2);
	mvpp2_cls_flow_port_id_sel(&fe, true);
	mvpp2_cls_flow_last_set(&fe, 0);
	mvpp2_cls_flow_pri_set(&fe, 0);
	mvpp2_cls_flow_seq_set(&fe, MVPP2_CLS_FLOW_SEQ_FIRST1);

	/* Add all ports */
	for (i = 0; i < MVPP2_MAX_PORTS; i++)
		mvpp2_cls_flow_port_add(&fe, BIT(i));

	mvpp2_cls_flow_write(priv, &fe);

	/* C3Hx lookups */
	for (i = 0; i < MVPP2_MAX_PORTS; i++) {
		memset(&fe, 0, sizeof(fe));
		fe.index = MVPP2_PORT_FLOW_HASH_ENTRY(i, flow->flow_id);

		mvpp2_cls_flow_port_id_sel(&fe, true);
		mvpp2_cls_flow_pri_set(&fe, i + 1);
		mvpp2_cls_flow_seq_set(&fe, MVPP2_CLS_FLOW_SEQ_MIDDLE);
		mvpp2_cls_flow_port_add(&fe, BIT(i));

		mvpp2_cls_flow_write(priv, &fe);
	}

	/* Update the last entry */
	mvpp2_cls_flow_last_set(&fe, 1);
	mvpp2_cls_flow_seq_set(&fe, MVPP2_CLS_FLOW_SEQ_LAST);

	mvpp2_cls_flow_write(priv, &fe);
}
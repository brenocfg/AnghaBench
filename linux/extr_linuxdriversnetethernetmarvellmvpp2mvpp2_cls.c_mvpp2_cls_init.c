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
struct mvpp2_cls_lookup_entry {int lkpid; int way; scalar_t__ data; } ;
struct mvpp2_cls_flow_entry {int index; int /*<<< orphan*/  data; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int MVPP2_CLS_FLOWS_TBL_SIZE ; 
 int MVPP2_CLS_LKP_TBL_SIZE ; 
 int /*<<< orphan*/  MVPP2_CLS_MODE_ACTIVE_MASK ; 
 int /*<<< orphan*/  MVPP2_CLS_MODE_REG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_write (struct mvpp2*,struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_cls_lookup_write (struct mvpp2*,struct mvpp2_cls_lookup_entry*) ; 
 int /*<<< orphan*/  mvpp2_cls_port_init_flows (struct mvpp2*) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mvpp2_cls_init(struct mvpp2 *priv)
{
	struct mvpp2_cls_lookup_entry le;
	struct mvpp2_cls_flow_entry fe;
	int index;

	/* Enable classifier */
	mvpp2_write(priv, MVPP2_CLS_MODE_REG, MVPP2_CLS_MODE_ACTIVE_MASK);

	/* Clear classifier flow table */
	memset(&fe.data, 0, sizeof(fe.data));
	for (index = 0; index < MVPP2_CLS_FLOWS_TBL_SIZE; index++) {
		fe.index = index;
		mvpp2_cls_flow_write(priv, &fe);
	}

	/* Clear classifier lookup table */
	le.data = 0;
	for (index = 0; index < MVPP2_CLS_LKP_TBL_SIZE; index++) {
		le.lkpid = index;
		le.way = 0;
		mvpp2_cls_lookup_write(priv, &le);

		le.way = 1;
		mvpp2_cls_lookup_write(priv, &le);
	}

	mvpp2_cls_port_init_flows(priv);
}
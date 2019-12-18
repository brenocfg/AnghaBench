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
struct mvpp2_cls_flow_entry {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL ; 

__attribute__((used)) static void mvpp2_cls_flow_port_id_sel(struct mvpp2_cls_flow_entry *fe,
				       bool from_packet)
{
	if (from_packet)
		fe->data[0] |= MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL;
	else
		fe->data[0] &= ~MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL;
}
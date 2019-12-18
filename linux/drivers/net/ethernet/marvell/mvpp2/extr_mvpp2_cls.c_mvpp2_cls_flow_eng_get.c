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
struct mvpp2_cls_flow_entry {int* data; } ;

/* Variables and functions */
 int MVPP2_CLS_FLOW_TBL0_ENG_MASK ; 
 int MVPP2_CLS_FLOW_TBL0_OFFS ; 

int mvpp2_cls_flow_eng_get(struct mvpp2_cls_flow_entry *fe)
{
	return (fe->data[0] >> MVPP2_CLS_FLOW_TBL0_OFFS) &
		MVPP2_CLS_FLOW_TBL0_ENG_MASK;
}
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
struct mvpp2_cls_flow {int dummy; } ;

/* Variables and functions */
 int MVPP2_N_FLOWS ; 
 struct mvpp2_cls_flow* cls_flows ; 

struct mvpp2_cls_flow *mvpp2_cls_flow_get(int flow)
{
	if (flow >= MVPP2_N_FLOWS)
		return NULL;

	return &cls_flows[flow];
}
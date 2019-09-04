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
typedef  int u8 ;
struct opa_vnic_adapter {int* flow_tbl; } ;

/* Variables and functions */
 int OPA_VNIC_FLOW_TBL_SIZE ; 

__attribute__((used)) static inline u8 opa_vnic_get_def_port(struct opa_vnic_adapter *adapter,
				       u8 entropy)
{
	u8 flow_id;

	/* Add the upper and lower 4-bits of entropy to get the flow id */
	flow_id = ((entropy & 0xf) + (entropy >> 4));
	return adapter->flow_tbl[flow_id & (OPA_VNIC_FLOW_TBL_SIZE - 1)];
}
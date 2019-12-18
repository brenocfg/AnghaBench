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
typedef  int u32 ;
struct opa_16b_mgmt {void* src_qpn; void* dest_qpn; } ;

/* Variables and functions */
 int OPA_16B_MGMT_QPN_MASK ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static inline void hfi1_16B_set_qpn(struct opa_16b_mgmt *mgmt,
				    u32 dest_qp, u32 src_qp)
{
	mgmt->dest_qpn = cpu_to_be32(dest_qp & OPA_16B_MGMT_QPN_MASK);
	mgmt->src_qpn = cpu_to_be32(src_qp & OPA_16B_MGMT_QPN_MASK);
}
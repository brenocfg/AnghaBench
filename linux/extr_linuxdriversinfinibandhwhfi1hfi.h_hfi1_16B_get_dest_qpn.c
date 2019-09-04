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
struct opa_16b_mgmt {int /*<<< orphan*/  dest_qpn; } ;

/* Variables and functions */
 int OPA_16B_MGMT_QPN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 hfi1_16B_get_dest_qpn(struct opa_16b_mgmt *mgmt)
{
	return be32_to_cpu(mgmt->dest_qpn) & OPA_16B_MGMT_QPN_MASK;
}
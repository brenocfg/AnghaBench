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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IBOE ; 
#define  OCRDMA_L3_TYPE_IB_GRH 130 
#define  OCRDMA_L3_TYPE_IPV4 129 
#define  OCRDMA_L3_TYPE_IPV6 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static u16 ocrdma_hdr_type_to_proto_num(int devid, u8 hdr_type)
{
	switch (hdr_type) {
	case OCRDMA_L3_TYPE_IB_GRH:
		return (u16)ETH_P_IBOE;
	case OCRDMA_L3_TYPE_IPV4:
		return (u16)0x0800;
	case OCRDMA_L3_TYPE_IPV6:
		return (u16)0x86dd;
	default:
		pr_err("ocrdma%d: Invalid network header\n", devid);
		return 0;
	}
}
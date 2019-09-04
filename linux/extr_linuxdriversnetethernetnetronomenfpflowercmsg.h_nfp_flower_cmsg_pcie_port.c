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
typedef  int u32 ;
typedef  enum nfp_flower_cmsg_port_vnic_type { ____Placeholder_nfp_flower_cmsg_port_vnic_type } nfp_flower_cmsg_port_vnic_type ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_PCI ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_PCIE_Q ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_TYPE ; 
 int NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC_TYPE ; 

__attribute__((used)) static inline u32
nfp_flower_cmsg_pcie_port(u8 nfp_pcie, enum nfp_flower_cmsg_port_vnic_type type,
			  u8 vnic, u8 q)
{
	return FIELD_PREP(NFP_FLOWER_CMSG_PORT_PCI, nfp_pcie) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_VNIC_TYPE, type) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_VNIC, vnic) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_PCIE_Q, q) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_TYPE,
			   NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT);
}
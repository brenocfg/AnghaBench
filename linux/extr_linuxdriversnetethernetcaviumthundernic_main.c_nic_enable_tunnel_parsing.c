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
typedef  unsigned long long u64 ;
struct nicpf {int dummy; } ;

/* Variables and functions */
 int ET_PROT ; 
 int ET_PROT_DEF ; 
 int IPV4_PROT ; 
 int IPV4_PROT_DEF ; 
 int IPV6_PROT ; 
 int IPV6_PROT_DEF ; 
 int /*<<< orphan*/  NIC_PF_RX_GENEVE_DEF ; 
 int /*<<< orphan*/  NIC_PF_RX_GENEVE_PROT_DEF ; 
 int /*<<< orphan*/  NIC_PF_RX_NVGRE_PROT_DEF ; 
 int /*<<< orphan*/  NIC_PF_RX_VXLAN_DEF_0_1 ; 
 int /*<<< orphan*/  NIC_PF_RX_VXLAN_PROT_DEF ; 
 unsigned long long UDP_GENEVE_PORT_NUM ; 
 unsigned long long UDP_VXLAN_PORT_NUM ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nic_enable_tunnel_parsing(struct nicpf *nic, int vf)
{
	u64 prot_def = (IPV6_PROT << 32) | (IPV4_PROT << 16) | ET_PROT;
	u64 vxlan_prot_def = (IPV6_PROT_DEF << 32) |
			      (IPV4_PROT_DEF) << 16 | ET_PROT_DEF;

	/* Configure tunnel parsing parameters */
	nic_reg_write(nic, NIC_PF_RX_GENEVE_DEF,
		      (1ULL << 63 | UDP_GENEVE_PORT_NUM));
	nic_reg_write(nic, NIC_PF_RX_GENEVE_PROT_DEF,
		      ((7ULL << 61) | prot_def));
	nic_reg_write(nic, NIC_PF_RX_NVGRE_PROT_DEF,
		      ((7ULL << 61) | prot_def));
	nic_reg_write(nic, NIC_PF_RX_VXLAN_DEF_0_1,
		      ((1ULL << 63) | UDP_VXLAN_PORT_NUM));
	nic_reg_write(nic, NIC_PF_RX_VXLAN_PROT_DEF,
		      ((0xfULL << 60) | vxlan_prot_def));
}
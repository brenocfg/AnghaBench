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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct be_res_desc_hdr {scalar_t__ desc_type; int desc_len; } ;
struct be_pcie_res_desc {scalar_t__ pf_type; scalar_t__ pf_num; scalar_t__ pf_state; } ;

/* Variables and functions */
 scalar_t__ MISSION_NIC ; 
 scalar_t__ MISSION_RDMA ; 
 scalar_t__ PCIE_RESOURCE_DESC_TYPE_V0 ; 
 scalar_t__ PCIE_RESOURCE_DESC_TYPE_V1 ; 
 int RESOURCE_DESC_SIZE_V0 ; 

__attribute__((used)) static u16 be_get_nic_pf_num_list(u8 *buf, u32 desc_count, u16 *nic_pf_nums)
{
	struct be_res_desc_hdr *hdr = (struct be_res_desc_hdr *)buf;
	struct be_pcie_res_desc *pcie = NULL;
	int i;
	u16 nic_pf_count = 0;

	for (i = 0; i < desc_count; i++) {
		if (hdr->desc_type == PCIE_RESOURCE_DESC_TYPE_V0 ||
		    hdr->desc_type == PCIE_RESOURCE_DESC_TYPE_V1) {
			pcie = (struct be_pcie_res_desc *)hdr;
			if (pcie->pf_state && (pcie->pf_type == MISSION_NIC ||
					       pcie->pf_type == MISSION_RDMA)) {
				nic_pf_nums[nic_pf_count++] = pcie->pf_num;
			}
		}

		hdr->desc_len = hdr->desc_len ? : RESOURCE_DESC_SIZE_V0;
		hdr = (void *)hdr + hdr->desc_len;
	}
	return nic_pf_count;
}
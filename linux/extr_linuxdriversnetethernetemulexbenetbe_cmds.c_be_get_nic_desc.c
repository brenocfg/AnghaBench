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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct be_res_desc_hdr {scalar_t__ desc_type; int desc_len; } ;
struct be_nic_res_desc {scalar_t__ pf_num; int flags; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ NIC_RESOURCE_DESC_TYPE_V0 ; 
 scalar_t__ NIC_RESOURCE_DESC_TYPE_V1 ; 
 scalar_t__ PF_NUM_IGNORE ; 
 int RESOURCE_DESC_SIZE_V0 ; 
 int /*<<< orphan*/  VFT_SHIFT ; 

__attribute__((used)) static struct be_nic_res_desc *be_get_nic_desc(u8 *buf, u32 desc_count,
					       bool get_vft, u8 pf_num)
{
	struct be_res_desc_hdr *hdr = (struct be_res_desc_hdr *)buf;
	struct be_nic_res_desc *nic;
	int i;

	for (i = 0; i < desc_count; i++) {
		if (hdr->desc_type == NIC_RESOURCE_DESC_TYPE_V0 ||
		    hdr->desc_type == NIC_RESOURCE_DESC_TYPE_V1) {
			nic = (struct be_nic_res_desc *)hdr;

			if ((pf_num == PF_NUM_IGNORE ||
			     nic->pf_num == pf_num) &&
			    (!get_vft || nic->flags & BIT(VFT_SHIFT)))
				return nic;
		}
		hdr->desc_len = hdr->desc_len ? : RESOURCE_DESC_SIZE_V0;
		hdr = (void *)hdr + hdr->desc_len;
	}
	return NULL;
}
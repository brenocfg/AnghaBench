#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  desc_len; int /*<<< orphan*/  desc_type; } ;
struct be_nic_res_desc {int flags; TYPE_1__ hdr; void* bw_max; scalar_t__ bw_min; int /*<<< orphan*/  vf_num; int /*<<< orphan*/  pf_num; } ;
struct be_adapter {int /*<<< orphan*/  pf_num; } ;

/* Variables and functions */
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 int IMM_SHIFT ; 
 int /*<<< orphan*/  NIC_RESOURCE_DESC_TYPE_V0 ; 
 int /*<<< orphan*/  NIC_RESOURCE_DESC_TYPE_V1 ; 
 int NOSV_SHIFT ; 
 int QUN_SHIFT ; 
 int /*<<< orphan*/  RESOURCE_DESC_SIZE_V0 ; 
 int /*<<< orphan*/  RESOURCE_DESC_SIZE_V1 ; 
 int be_cmd_set_profile_config (struct be_adapter*,struct be_nic_res_desc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int be_cmd_set_qos (struct be_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_reset_nic_desc (struct be_nic_res_desc*) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 

int be_cmd_config_qos(struct be_adapter *adapter, u32 max_rate, u16 link_speed,
		      u8 domain)
{
	struct be_nic_res_desc nic_desc;
	u32 bw_percent;
	u16 version = 0;

	if (BE3_chip(adapter))
		return be_cmd_set_qos(adapter, max_rate / 10, domain);

	be_reset_nic_desc(&nic_desc);
	nic_desc.pf_num = adapter->pf_num;
	nic_desc.vf_num = domain;
	nic_desc.bw_min = 0;
	if (lancer_chip(adapter)) {
		nic_desc.hdr.desc_type = NIC_RESOURCE_DESC_TYPE_V0;
		nic_desc.hdr.desc_len = RESOURCE_DESC_SIZE_V0;
		nic_desc.flags = (1 << QUN_SHIFT) | (1 << IMM_SHIFT) |
					(1 << NOSV_SHIFT);
		nic_desc.bw_max = cpu_to_le32(max_rate / 10);
	} else {
		version = 1;
		nic_desc.hdr.desc_type = NIC_RESOURCE_DESC_TYPE_V1;
		nic_desc.hdr.desc_len = RESOURCE_DESC_SIZE_V1;
		nic_desc.flags = (1 << IMM_SHIFT) | (1 << NOSV_SHIFT);
		bw_percent = max_rate ? (max_rate * 100) / link_speed : 100;
		nic_desc.bw_max = cpu_to_le32(bw_percent);
	}

	return be_cmd_set_profile_config(adapter, &nic_desc,
					 nic_desc.hdr.desc_len,
					 1, version, domain);
}
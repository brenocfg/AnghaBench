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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct enic {int /*<<< orphan*/  vdev; } ;
typedef  enum vnic_devcmd_cmd { ____Placeholder_vnic_devcmd_cmd } vnic_devcmd_cmd ;

/* Variables and functions */
 int CMD_NIC_CFG ; 
 int CMD_NIC_CFG_CHK ; 
 int NIC_CFG_RSS_HASH_TYPE_UDP_IPV4 ; 
 int NIC_CFG_RSS_HASH_TYPE_UDP_IPV6 ; 
 int vnic_dev_cmd (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  vnic_set_nic_cfg (scalar_t__*,int,int,int,int,int,int,int) ; 

int enic_set_nic_cfg(struct enic *enic, u8 rss_default_cpu, u8 rss_hash_type,
	u8 rss_hash_bits, u8 rss_base_cpu, u8 rss_enable, u8 tso_ipid_split_en,
	u8 ig_vlan_strip_en)
{
	enum vnic_devcmd_cmd cmd = CMD_NIC_CFG;
	u64 a0, a1;
	u32 nic_cfg;
	int wait = 1000;

	vnic_set_nic_cfg(&nic_cfg, rss_default_cpu,
		rss_hash_type, rss_hash_bits, rss_base_cpu,
		rss_enable, tso_ipid_split_en, ig_vlan_strip_en);

	a0 = nic_cfg;
	a1 = 0;

	if (rss_hash_type & (NIC_CFG_RSS_HASH_TYPE_UDP_IPV4 |
			     NIC_CFG_RSS_HASH_TYPE_UDP_IPV6))
		cmd = CMD_NIC_CFG_CHK;

	return vnic_dev_cmd(enic->vdev, cmd, &a0, &a1, wait);
}
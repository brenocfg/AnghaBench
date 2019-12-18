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

/* Variables and functions */
 int NIC_CFG_IG_VLAN_STRIP_EN_MASK_FIELD ; 
 int NIC_CFG_IG_VLAN_STRIP_EN_SHIFT ; 
 int NIC_CFG_RSS_BASE_CPU_MASK_FIELD ; 
 int NIC_CFG_RSS_BASE_CPU_SHIFT ; 
 int NIC_CFG_RSS_DEFAULT_CPU_MASK_FIELD ; 
 int NIC_CFG_RSS_ENABLE_MASK_FIELD ; 
 int NIC_CFG_RSS_ENABLE_SHIFT ; 
 int NIC_CFG_RSS_HASH_BITS_MASK_FIELD ; 
 int NIC_CFG_RSS_HASH_BITS_SHIFT ; 
 int NIC_CFG_RSS_HASH_TYPE_MASK_FIELD ; 
 int NIC_CFG_RSS_HASH_TYPE_SHIFT ; 
 int NIC_CFG_TSO_IPID_SPLIT_EN_MASK_FIELD ; 
 int NIC_CFG_TSO_IPID_SPLIT_EN_SHIFT ; 

__attribute__((used)) static inline void vnic_set_nic_cfg(u32 *nic_cfg,
	u8 rss_default_cpu, u8 rss_hash_type,
	u8 rss_hash_bits, u8 rss_base_cpu,
	u8 rss_enable, u8 tso_ipid_split_en,
	u8 ig_vlan_strip_en)
{
	*nic_cfg = (rss_default_cpu & NIC_CFG_RSS_DEFAULT_CPU_MASK_FIELD) |
		((rss_hash_type & NIC_CFG_RSS_HASH_TYPE_MASK_FIELD)
			<< NIC_CFG_RSS_HASH_TYPE_SHIFT) |
		((rss_hash_bits & NIC_CFG_RSS_HASH_BITS_MASK_FIELD)
			<< NIC_CFG_RSS_HASH_BITS_SHIFT) |
		((rss_base_cpu & NIC_CFG_RSS_BASE_CPU_MASK_FIELD)
			<< NIC_CFG_RSS_BASE_CPU_SHIFT) |
		((rss_enable & NIC_CFG_RSS_ENABLE_MASK_FIELD)
			<< NIC_CFG_RSS_ENABLE_SHIFT) |
		((tso_ipid_split_en & NIC_CFG_TSO_IPID_SPLIT_EN_MASK_FIELD)
			<< NIC_CFG_TSO_IPID_SPLIT_EN_SHIFT) |
		((ig_vlan_strip_en & NIC_CFG_IG_VLAN_STRIP_EN_MASK_FIELD)
			<< NIC_CFG_IG_VLAN_STRIP_EN_SHIFT);
}
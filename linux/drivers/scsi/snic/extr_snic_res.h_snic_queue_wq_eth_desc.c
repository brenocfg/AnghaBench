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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct wq_enet_desc {int dummy; } ;
struct vnic_wq {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int VNIC_PADDR_TARGET ; 
 struct wq_enet_desc* svnic_wq_next_desc (struct vnic_wq*) ; 
 int /*<<< orphan*/  svnic_wq_post (struct vnic_wq*,void*,scalar_t__,unsigned int,int,int) ; 
 int /*<<< orphan*/  wq_enet_desc_enc (struct wq_enet_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
snic_queue_wq_eth_desc(struct vnic_wq *wq,
		       void *os_buf,
		       dma_addr_t dma_addr,
		       unsigned int len,
		       int vlan_tag_insert,
		       unsigned int vlan_tag,
		       int cq_entry)
{
	struct wq_enet_desc *desc = svnic_wq_next_desc(wq);

	wq_enet_desc_enc(desc,
			(u64)dma_addr | VNIC_PADDR_TARGET,
			(u16)len,
			0, /* mss_or_csum_offset */
			0, /* fc_eof */
			0, /* offload mode */
			1, /* eop */
			(u8)cq_entry,
			0, /* fcoe_encap */
			(u8)vlan_tag_insert,
			(u16)vlan_tag,
			0 /* loopback */);

	svnic_wq_post(wq, os_buf, dma_addr, len, 1, 1);
}
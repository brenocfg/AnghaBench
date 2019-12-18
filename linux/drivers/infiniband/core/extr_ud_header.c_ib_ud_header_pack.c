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
struct ib_ud_header {int /*<<< orphan*/  immediate_data; scalar_t__ immediate_present; int /*<<< orphan*/  deth; int /*<<< orphan*/  bth; int /*<<< orphan*/  udp; scalar_t__ udp_present; int /*<<< orphan*/  ip4; scalar_t__ ipv4_present; int /*<<< orphan*/  grh; scalar_t__ grh_present; int /*<<< orphan*/  vlan; scalar_t__ vlan_present; int /*<<< orphan*/  eth; scalar_t__ eth_present; int /*<<< orphan*/  lrh; scalar_t__ lrh_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_BTH_BYTES ; 
 scalar_t__ IB_DETH_BYTES ; 
 scalar_t__ IB_ETH_BYTES ; 
 scalar_t__ IB_GRH_BYTES ; 
 scalar_t__ IB_IP4_BYTES ; 
 scalar_t__ IB_LRH_BYTES ; 
 scalar_t__ IB_UDP_BYTES ; 
 scalar_t__ IB_VLAN_BYTES ; 
 int /*<<< orphan*/  bth_table ; 
 int /*<<< orphan*/  deth_table ; 
 int /*<<< orphan*/  eth_table ; 
 int /*<<< orphan*/  grh_table ; 
 int /*<<< orphan*/  ib_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ip4_table ; 
 int /*<<< orphan*/  lrh_table ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udp_table ; 
 int /*<<< orphan*/  vlan_table ; 

int ib_ud_header_pack(struct ib_ud_header *header,
		      void                *buf)
{
	int len = 0;

	if (header->lrh_present) {
		ib_pack(lrh_table, ARRAY_SIZE(lrh_table),
			&header->lrh, buf + len);
		len += IB_LRH_BYTES;
	}
	if (header->eth_present) {
		ib_pack(eth_table, ARRAY_SIZE(eth_table),
			&header->eth, buf + len);
		len += IB_ETH_BYTES;
	}
	if (header->vlan_present) {
		ib_pack(vlan_table, ARRAY_SIZE(vlan_table),
			&header->vlan, buf + len);
		len += IB_VLAN_BYTES;
	}
	if (header->grh_present) {
		ib_pack(grh_table, ARRAY_SIZE(grh_table),
			&header->grh, buf + len);
		len += IB_GRH_BYTES;
	}
	if (header->ipv4_present) {
		ib_pack(ip4_table, ARRAY_SIZE(ip4_table),
			&header->ip4, buf + len);
		len += IB_IP4_BYTES;
	}
	if (header->udp_present) {
		ib_pack(udp_table, ARRAY_SIZE(udp_table),
			&header->udp, buf + len);
		len += IB_UDP_BYTES;
	}

	ib_pack(bth_table, ARRAY_SIZE(bth_table),
		&header->bth, buf + len);
	len += IB_BTH_BYTES;

	ib_pack(deth_table, ARRAY_SIZE(deth_table),
		&header->deth, buf + len);
	len += IB_DETH_BYTES;

	if (header->immediate_present) {
		memcpy(buf + len, &header->immediate_data, sizeof header->immediate_data);
		len += sizeof header->immediate_data;
	}

	return len;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pci_dev {int revision; } ;
struct hns3_enet_ring {TYPE_1__* tqp; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  ot_vlan_tag; } ;
struct hns3_desc {TYPE_2__ rx; } ;
struct hnae3_handle {int /*<<< orphan*/  port_base_vlan_state; struct pci_dev* pdev; } ;
struct TYPE_3__ {struct hnae3_handle* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_PORT_BASE_VLAN_DISABLE ; 
 int /*<<< orphan*/  HNS3_RXD_STRP_TAGP_M ; 
 int /*<<< orphan*/  HNS3_RXD_STRP_TAGP_S ; 
#define  HNS3_STRP_BOTH 130 
#define  HNS3_STRP_INNER_VLAN 129 
#define  HNS3_STRP_OUTER_VLAN 128 
 int VLAN_VID_MASK ; 
 int hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hns3_parse_vlan_tag(struct hns3_enet_ring *ring,
				struct hns3_desc *desc, u32 l234info,
				u16 *vlan_tag)
{
	struct hnae3_handle *handle = ring->tqp->handle;
	struct pci_dev *pdev = ring->tqp->handle->pdev;

	if (pdev->revision == 0x20) {
		*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		if (!(*vlan_tag & VLAN_VID_MASK))
			*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);

		return (*vlan_tag != 0);
	}

#define HNS3_STRP_OUTER_VLAN	0x1
#define HNS3_STRP_INNER_VLAN	0x2
#define HNS3_STRP_BOTH		0x3

	/* Hardware always insert VLAN tag into RX descriptor when
	 * remove the tag from packet, driver needs to determine
	 * reporting which tag to stack.
	 */
	switch (hnae3_get_field(l234info, HNS3_RXD_STRP_TAGP_M,
				HNS3_RXD_STRP_TAGP_S)) {
	case HNS3_STRP_OUTER_VLAN:
		if (handle->port_base_vlan_state !=
				HNAE3_PORT_BASE_VLAN_DISABLE)
			return false;

		*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		return true;
	case HNS3_STRP_INNER_VLAN:
		if (handle->port_base_vlan_state !=
				HNAE3_PORT_BASE_VLAN_DISABLE)
			return false;

		*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);
		return true;
	case HNS3_STRP_BOTH:
		if (handle->port_base_vlan_state ==
				HNAE3_PORT_BASE_VLAN_DISABLE)
			*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		else
			*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);

		return true;
	default:
		return false;
	}
}
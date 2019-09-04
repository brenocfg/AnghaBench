#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pci_dev {int revision; } ;
struct hns3_enet_ring {TYPE_2__* tqp; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  ot_vlan_tag; } ;
struct hns3_desc {TYPE_3__ rx; } ;
struct TYPE_5__ {TYPE_1__* handle; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_RXD_STRP_TAGP_M ; 
 int /*<<< orphan*/  HNS3_RXD_STRP_TAGP_S ; 
 int VLAN_VID_MASK ; 
 int hnae3_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 hns3_parse_vlan_tag(struct hns3_enet_ring *ring,
			       struct hns3_desc *desc, u32 l234info)
{
	struct pci_dev *pdev = ring->tqp->handle->pdev;
	u16 vlan_tag;

	if (pdev->revision == 0x20) {
		vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		if (!(vlan_tag & VLAN_VID_MASK))
			vlan_tag = le16_to_cpu(desc->rx.vlan_tag);

		return vlan_tag;
	}

#define HNS3_STRP_OUTER_VLAN	0x1
#define HNS3_STRP_INNER_VLAN	0x2

	switch (hnae3_get_field(l234info, HNS3_RXD_STRP_TAGP_M,
				HNS3_RXD_STRP_TAGP_S)) {
	case HNS3_STRP_OUTER_VLAN:
		vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		break;
	case HNS3_STRP_INNER_VLAN:
		vlan_tag = le16_to_cpu(desc->rx.vlan_tag);
		break;
	default:
		vlan_tag = 0;
		break;
	}

	return vlan_tag;
}
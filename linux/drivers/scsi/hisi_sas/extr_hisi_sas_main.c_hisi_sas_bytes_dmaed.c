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
struct sas_phy {scalar_t__ minimum_linkrate; scalar_t__ maximum_linkrate; int /*<<< orphan*/  maximum_linkrate_hw; int /*<<< orphan*/  minimum_linkrate_hw; int /*<<< orphan*/  negotiated_linkrate; } ;
struct sas_identify_frame {int /*<<< orphan*/  target_bits; int /*<<< orphan*/  initiator_bits; int /*<<< orphan*/  dev_type; } ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* notify_phy_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  target_port_protocols; int /*<<< orphan*/  device_type; } ;
struct asd_sas_phy {int /*<<< orphan*/  frame_rcvd_size; int /*<<< orphan*/  linkrate; struct sas_phy* phy; } ;
struct hisi_sas_phy {scalar_t__ minimum_linkrate; scalar_t__ maximum_linkrate; int phy_type; int /*<<< orphan*/  frame_rcvd_size; TYPE_2__ identify; scalar_t__ frame_rcvd; int /*<<< orphan*/  phy_attached; struct asd_sas_phy sas_phy; } ;
struct hisi_hba {TYPE_1__* hw; struct sas_ha_struct sha; struct hisi_sas_phy* phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_get_max_linkrate ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHYE_OOB_DONE ; 
 int /*<<< orphan*/  PORTE_BYTES_DMAED ; 
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 int /*<<< orphan*/  SAS_LINK_RATE_1_5_GBPS ; 
 scalar_t__ SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_sas_bytes_dmaed(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_ha_struct *sas_ha;

	if (!phy->phy_attached)
		return;

	sas_ha = &hisi_hba->sha;
	sas_ha->notify_phy_event(sas_phy, PHYE_OOB_DONE);

	if (sas_phy->phy) {
		struct sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_linkrate = sas_phy->linkrate;
		sphy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		sphy->maximum_linkrate_hw =
			hisi_hba->hw->phy_get_max_linkrate();
		if (sphy->minimum_linkrate == SAS_LINK_RATE_UNKNOWN)
			sphy->minimum_linkrate = phy->minimum_linkrate;

		if (sphy->maximum_linkrate == SAS_LINK_RATE_UNKNOWN)
			sphy->maximum_linkrate = phy->maximum_linkrate;
	}

	if (phy->phy_type & PORT_TYPE_SAS) {
		struct sas_identify_frame *id;

		id = (struct sas_identify_frame *)phy->frame_rcvd;
		id->dev_type = phy->identify.device_type;
		id->initiator_bits = SAS_PROTOCOL_ALL;
		id->target_bits = phy->identify.target_port_protocols;
	} else if (phy->phy_type & PORT_TYPE_SATA) {
		/* Nothing */
	}

	sas_phy->frame_rcvd_size = phy->frame_rcvd_size;
	sas_ha->notify_port_event(sas_phy, PORTE_BYTES_DMAED);
}
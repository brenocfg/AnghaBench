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
struct sas_phy {int /*<<< orphan*/  maximum_linkrate_hw; int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate_hw; int /*<<< orphan*/  minimum_linkrate; int /*<<< orphan*/  negotiated_linkrate; } ;
struct sas_identify_frame {int /*<<< orphan*/  target_bits; int /*<<< orphan*/  initiator_bits; int /*<<< orphan*/  dev_type; } ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* notify_phy_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  target_port_protocols; int /*<<< orphan*/  device_type; } ;
struct asd_sas_phy {int /*<<< orphan*/  frame_rcvd_size; int /*<<< orphan*/  linkrate; struct sas_phy* phy; } ;
struct mvs_phy {int att_dev_info; int phy_type; int /*<<< orphan*/  frame_rcvd_size; TYPE_1__ identify; scalar_t__ frame_rcvd; int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; int /*<<< orphan*/  phy_attached; struct asd_sas_phy sas_phy; } ;
struct mvs_info {int id; struct sas_ha_struct* sas; TYPE_2__* chip; struct mvs_phy* phy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_port_cfg_data ) (struct mvs_info*,int,int) ;int /*<<< orphan*/  (* write_port_cfg_addr ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_max_link_rate ) () ;} ;
struct TYPE_5__ {int n_phy; } ;

/* Variables and functions */
 TYPE_3__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  PHYE_OOB_DONE ; 
 int /*<<< orphan*/  PHYR_PHY_STAT ; 
 int /*<<< orphan*/  PORTE_BYTES_DMAED ; 
 int PORT_DEV_TRGT_MASK ; 
 int PORT_SSP_TRGT_MASK ; 
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 int /*<<< orphan*/  SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/  mv_dprintk (char*,int) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvs_bytes_dmaed(struct mvs_info *mvi, int i)
{
	struct mvs_phy *phy = &mvi->phy[i];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_ha_struct *sas_ha;
	if (!phy->phy_attached)
		return;

	if (!(phy->att_dev_info & PORT_DEV_TRGT_MASK)
		&& phy->phy_type & PORT_TYPE_SAS) {
		return;
	}

	sas_ha = mvi->sas;
	sas_ha->notify_phy_event(sas_phy, PHYE_OOB_DONE);

	if (sas_phy->phy) {
		struct sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_linkrate = sas_phy->linkrate;
		sphy->minimum_linkrate = phy->minimum_linkrate;
		sphy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		sphy->maximum_linkrate = phy->maximum_linkrate;
		sphy->maximum_linkrate_hw = MVS_CHIP_DISP->phy_max_link_rate();
	}

	if (phy->phy_type & PORT_TYPE_SAS) {
		struct sas_identify_frame *id;

		id = (struct sas_identify_frame *)phy->frame_rcvd;
		id->dev_type = phy->identify.device_type;
		id->initiator_bits = SAS_PROTOCOL_ALL;
		id->target_bits = phy->identify.target_port_protocols;

		/* direct attached SAS device */
		if (phy->att_dev_info & PORT_SSP_TRGT_MASK) {
			MVS_CHIP_DISP->write_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
			MVS_CHIP_DISP->write_port_cfg_data(mvi, i, 0x00);
		}
	} else if (phy->phy_type & PORT_TYPE_SATA) {
		/*Nothing*/
	}
	mv_dprintk("phy %d byte dmaded.\n", i + mvi->id * mvi->chip->n_phy);

	sas_phy->frame_rcvd_size = phy->frame_rcvd_size;

	mvi->sas->notify_port_event(sas_phy,
				   PORTE_BYTES_DMAED);
}
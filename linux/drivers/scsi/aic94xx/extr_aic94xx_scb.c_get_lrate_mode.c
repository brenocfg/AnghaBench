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
typedef  int u8 ;
struct sas_phy {int /*<<< orphan*/  minimum_linkrate; int /*<<< orphan*/  maximum_linkrate; void* minimum_linkrate_hw; void* maximum_linkrate_hw; void* negotiated_linkrate; } ;
struct TYPE_4__ {int /*<<< orphan*/  oob_mode; void* linkrate; struct sas_phy* phy; } ;
struct asd_phy {TYPE_2__ sas_phy; TYPE_1__* phy_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  min_sas_lrate; int /*<<< orphan*/  max_sas_lrate; } ;

/* Variables and functions */
#define  PHY_SPEED_15 130 
#define  PHY_SPEED_30 129 
#define  PHY_SPEED_60 128 
 void* SAS_LINK_RATE_1_5_GBPS ; 
 void* SAS_LINK_RATE_3_0_GBPS ; 
 void* SAS_LINK_RATE_6_0_GBPS ; 
 int SAS_MODE ; 
 int /*<<< orphan*/  SAS_OOB_MODE ; 
 int SATA_MODE ; 
 int /*<<< orphan*/  SATA_OOB_MODE ; 

__attribute__((used)) static void get_lrate_mode(struct asd_phy *phy, u8 oob_mode)
{
	struct sas_phy *sas_phy = phy->sas_phy.phy;

	switch (oob_mode & 7) {
	case PHY_SPEED_60:
		/* FIXME: sas transport class doesn't have this */
		phy->sas_phy.linkrate = SAS_LINK_RATE_6_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_6_0_GBPS;
		break;
	case PHY_SPEED_30:
		phy->sas_phy.linkrate = SAS_LINK_RATE_3_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_3_0_GBPS;
		break;
	case PHY_SPEED_15:
		phy->sas_phy.linkrate = SAS_LINK_RATE_1_5_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_1_5_GBPS;
		break;
	}
	sas_phy->negotiated_linkrate = phy->sas_phy.linkrate;
	sas_phy->maximum_linkrate_hw = SAS_LINK_RATE_3_0_GBPS;
	sas_phy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
	sas_phy->maximum_linkrate = phy->phy_desc->max_sas_lrate;
	sas_phy->minimum_linkrate = phy->phy_desc->min_sas_lrate;

	if (oob_mode & SAS_MODE)
		phy->sas_phy.oob_mode = SAS_OOB_MODE;
	else if (oob_mode & SATA_MODE)
		phy->sas_phy.oob_mode = SATA_OOB_MODE;
}
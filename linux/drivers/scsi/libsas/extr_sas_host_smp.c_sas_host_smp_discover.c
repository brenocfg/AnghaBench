#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_8__ {int device_type; size_t initiator_port_protocols; size_t target_port_protocols; } ;
struct sas_rphy {TYPE_4__ identify; } ;
struct sas_phy {size_t negotiated_linkrate; int minimum_linkrate; int minimum_linkrate_hw; int maximum_linkrate; int maximum_linkrate_hw; } ;
struct sas_ha_struct {size_t num_phys; TYPE_3__** sas_phy; int /*<<< orphan*/  sas_addr; } ;
struct TYPE_7__ {TYPE_2__* port; int /*<<< orphan*/  attached_sas_addr; struct sas_phy* phy; } ;
struct TYPE_6__ {TYPE_1__* port_dev; } ;
struct TYPE_5__ {struct sas_rphy* rphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 size_t SMP_RESP_FUNC_ACC ; 
 size_t SMP_RESP_NO_PHY ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_host_smp_discover(struct sas_ha_struct *sas_ha, u8 *resp_data,
				  u8 phy_id)
{
	struct sas_phy *phy;
	struct sas_rphy *rphy;

	if (phy_id >= sas_ha->num_phys) {
		resp_data[2] = SMP_RESP_NO_PHY;
		return;
	}
	resp_data[2] = SMP_RESP_FUNC_ACC;

	phy = sas_ha->sas_phy[phy_id]->phy;
	resp_data[9] = phy_id;
	resp_data[13] = phy->negotiated_linkrate;
	memcpy(resp_data + 16, sas_ha->sas_addr, SAS_ADDR_SIZE);
	memcpy(resp_data + 24, sas_ha->sas_phy[phy_id]->attached_sas_addr,
	       SAS_ADDR_SIZE);
	resp_data[40] = (phy->minimum_linkrate << 4) |
		phy->minimum_linkrate_hw;
	resp_data[41] = (phy->maximum_linkrate << 4) |
		phy->maximum_linkrate_hw;

	if (!sas_ha->sas_phy[phy_id]->port ||
	    !sas_ha->sas_phy[phy_id]->port->port_dev)
		return;

	rphy = sas_ha->sas_phy[phy_id]->port->port_dev->rphy;
	resp_data[12] = rphy->identify.device_type << 4;
	resp_data[14] = rphy->identify.initiator_port_protocols;
	resp_data[15] = rphy->identify.target_port_protocols;
}
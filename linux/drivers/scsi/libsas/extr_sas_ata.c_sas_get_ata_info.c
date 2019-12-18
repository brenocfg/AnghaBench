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
struct ex_phy {int attached_tproto; scalar_t__ attached_dev_type; int /*<<< orphan*/  phy_id; scalar_t__ attached_sata_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  fis; } ;
struct TYPE_8__ {TYPE_1__ rps; } ;
struct TYPE_6__ {int /*<<< orphan*/  class; TYPE_4__ rps_resp; } ;
struct domain_device {int tproto; int dev_type; TYPE_2__ sata_dev; int /*<<< orphan*/  frame_rcvd; TYPE_3__* parent; } ;
struct dev_to_host_fis {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  sas_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int SAS_PROTOCOL_STP ; 
 int SAS_SATA_DEV ; 
 scalar_t__ SAS_SATA_PENDING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sas_get_ata_command_set (struct domain_device*) ; 
 int sas_get_report_phy_sata (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

int sas_get_ata_info(struct domain_device *dev, struct ex_phy *phy)
{
	if (phy->attached_tproto & SAS_PROTOCOL_STP)
		dev->tproto = phy->attached_tproto;
	if (phy->attached_sata_dev)
		dev->tproto |= SAS_SATA_DEV;

	if (phy->attached_dev_type == SAS_SATA_PENDING)
		dev->dev_type = SAS_SATA_PENDING;
	else {
		int res;

		dev->dev_type = SAS_SATA_DEV;
		res = sas_get_report_phy_sata(dev->parent, phy->phy_id,
					      &dev->sata_dev.rps_resp);
		if (res) {
			pr_debug("report phy sata to %016llx:%02d returned 0x%x\n",
				 SAS_ADDR(dev->parent->sas_addr),
				 phy->phy_id, res);
			return res;
		}
		memcpy(dev->frame_rcvd, &dev->sata_dev.rps_resp.rps.fis,
		       sizeof(struct dev_to_host_fis));
		dev->sata_dev.class = sas_get_ata_command_set(dev);
	}
	return 0;
}
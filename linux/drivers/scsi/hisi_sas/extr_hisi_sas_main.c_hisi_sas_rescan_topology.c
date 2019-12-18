#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;} ;
struct asd_sas_phy {TYPE_1__* phy; struct asd_sas_port* port; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {int n_phy; struct hisi_sas_phy* phy; struct sas_ha_struct sha; } ;
struct domain_device {int /*<<< orphan*/  dev_type; } ;
struct asd_sas_port {struct domain_device* port_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_down (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_sas_rescan_topology(struct hisi_hba *hisi_hba, u32 state)
{
	struct sas_ha_struct *sas_ha = &hisi_hba->sha;
	struct asd_sas_port *_sas_port = NULL;
	int phy_no;

	for (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
		struct asd_sas_phy *sas_phy = &phy->sas_phy;
		struct asd_sas_port *sas_port = sas_phy->port;
		bool do_port_check = !!(_sas_port != sas_port);

		if (!sas_phy->phy->enabled)
			continue;

		/* Report PHY state change to libsas */
		if (state & BIT(phy_no)) {
			if (do_port_check && sas_port && sas_port->port_dev) {
				struct domain_device *dev = sas_port->port_dev;

				_sas_port = sas_port;

				if (dev_is_expander(dev->dev_type))
					sas_ha->notify_port_event(sas_phy,
							PORTE_BROADCAST_RCVD);
			}
		} else {
			hisi_sas_phy_down(hisi_hba, phy_no, 0);
		}

	}
}
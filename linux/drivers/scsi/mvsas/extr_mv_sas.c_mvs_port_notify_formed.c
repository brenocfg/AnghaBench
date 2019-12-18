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
struct sas_ha_struct {scalar_t__ lldd_ha; struct asd_sas_phy** sas_phy; } ;
struct mvs_prv_info {int n_phy; struct mvs_info** mvi; } ;
struct mvs_port {int port_attached; int /*<<< orphan*/  wide_port_phymap; } ;
struct mvs_phy {int phy_type; int att_dev_info; struct mvs_port* port; } ;
struct mvs_info {int /*<<< orphan*/  lock; struct mvs_port* port; TYPE_1__* chip; } ;
struct asd_sas_port {int /*<<< orphan*/  phy_mask; struct mvs_port* lldd_port; } ;
struct asd_sas_phy {int /*<<< orphan*/  id; struct asd_sas_port* port; struct mvs_phy* lldd_phy; struct sas_ha_struct* ha; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_port_cfg_data ) (struct mvs_info*,int,int) ;int /*<<< orphan*/  (* write_port_cfg_addr ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int n_phy; } ;

/* Variables and functions */
 TYPE_2__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  PHYR_PHY_STAT ; 
 int PORT_SSP_TRGT_MASK ; 
 int PORT_TYPE_SAS ; 
 int /*<<< orphan*/  mv_printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_update_wideport (struct mvs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mvs_info*,int,int) ; 

__attribute__((used)) static void mvs_port_notify_formed(struct asd_sas_phy *sas_phy, int lock)
{
	struct sas_ha_struct *sas_ha = sas_phy->ha;
	struct mvs_info *mvi = NULL; int i = 0, hi;
	struct mvs_phy *phy = sas_phy->lldd_phy;
	struct asd_sas_port *sas_port = sas_phy->port;
	struct mvs_port *port;
	unsigned long flags = 0;
	if (!sas_port)
		return;

	while (sas_ha->sas_phy[i]) {
		if (sas_ha->sas_phy[i] == sas_phy)
			break;
		i++;
	}
	hi = i/((struct mvs_prv_info *)sas_ha->lldd_ha)->n_phy;
	mvi = ((struct mvs_prv_info *)sas_ha->lldd_ha)->mvi[hi];
	if (i >= mvi->chip->n_phy)
		port = &mvi->port[i - mvi->chip->n_phy];
	else
		port = &mvi->port[i];
	if (lock)
		spin_lock_irqsave(&mvi->lock, flags);
	port->port_attached = 1;
	phy->port = port;
	sas_port->lldd_port = port;
	if (phy->phy_type & PORT_TYPE_SAS) {
		port->wide_port_phymap = sas_port->phy_mask;
		mv_printk("set wide port phy map %x\n", sas_port->phy_mask);
		mvs_update_wideport(mvi, sas_phy->id);

		/* direct attached SAS device */
		if (phy->att_dev_info & PORT_SSP_TRGT_MASK) {
			MVS_CHIP_DISP->write_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
			MVS_CHIP_DISP->write_port_cfg_data(mvi, i, 0x04);
		}
	}
	if (lock)
		spin_unlock_irqrestore(&mvi->lock, flags);
}
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
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ expires; int /*<<< orphan*/ * function; } ;
struct mvs_phy {int irq_status; int phy_event; int phy_type; int phy_status; int /*<<< orphan*/  sas_phy; TYPE_2__ timer; } ;
struct mvs_info {int id; TYPE_1__* chip; struct mvs_phy* phy; } ;
struct TYPE_6__ {int (* read_port_irq_stat ) (struct mvs_info*,int) ;int (* read_port_irq_mask ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* phy_reset ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_port_irq_mask ) (struct mvs_info*,int,int) ;int /*<<< orphan*/  (* detect_porttype ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* stp_reset ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* clear_srs_irq ) (struct mvs_info*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_phy_ctl ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* write_port_irq_stat ) (struct mvs_info*,int,int) ;} ;
struct TYPE_4__ {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXP_BRCT_CHG ; 
 int HZ ; 
 TYPE_3__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  MVS_PHY_TUNE ; 
 int /*<<< orphan*/  MVS_SOFT_RESET ; 
 int PHYEV_BROAD_CH ; 
 int PHYEV_COMWAKE ; 
 int PHYEV_DCDR_ERR ; 
 int PHYEV_ID_DONE ; 
 int PHYEV_POOF ; 
 int PHYEV_SIG_FIS ; 
 int /*<<< orphan*/  PHY_PLUG_EVENT ; 
 int PHY_PLUG_OUT ; 
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mv_dprintk (char*,int,...) ; 
 int /*<<< orphan*/  mvs_bytes_dmaed (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_do_release_task (struct mvs_info*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvs_handle_event (struct mvs_info*,void*,int /*<<< orphan*/ ) ; 
 void* mvs_is_phy_ready (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_port_notify_formed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mvs_sig_time_out ; 
 int /*<<< orphan*/  mvs_update_phyinfo (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct mvs_info*,int) ; 
 int stub10 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub11 (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub4 (struct mvs_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub6 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int stub7 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub8 (struct mvs_info*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct mvs_info*,int) ; 

void mvs_int_port(struct mvs_info *mvi, int phy_no, u32 events)
{
	u32 tmp;
	struct mvs_phy *phy = &mvi->phy[phy_no];

	phy->irq_status = MVS_CHIP_DISP->read_port_irq_stat(mvi, phy_no);
	MVS_CHIP_DISP->write_port_irq_stat(mvi, phy_no, phy->irq_status);
	mv_dprintk("phy %d ctrl sts=0x%08X.\n", phy_no+mvi->id*mvi->chip->n_phy,
		MVS_CHIP_DISP->read_phy_ctl(mvi, phy_no));
	mv_dprintk("phy %d irq sts = 0x%08X\n", phy_no+mvi->id*mvi->chip->n_phy,
		phy->irq_status);

	/*
	* events is port event now ,
	* we need check the interrupt status which belongs to per port.
	*/

	if (phy->irq_status & PHYEV_DCDR_ERR) {
		mv_dprintk("phy %d STP decoding error.\n",
		phy_no + mvi->id*mvi->chip->n_phy);
	}

	if (phy->irq_status & PHYEV_POOF) {
		mdelay(500);
		if (!(phy->phy_event & PHY_PLUG_OUT)) {
			int dev_sata = phy->phy_type & PORT_TYPE_SATA;
			int ready;
			mvs_do_release_task(mvi, phy_no, NULL);
			phy->phy_event |= PHY_PLUG_OUT;
			MVS_CHIP_DISP->clear_srs_irq(mvi, 0, 1);
			mvs_handle_event(mvi,
				(void *)(unsigned long)phy_no,
				PHY_PLUG_EVENT);
			ready = mvs_is_phy_ready(mvi, phy_no);
			if (ready || dev_sata) {
				if (MVS_CHIP_DISP->stp_reset)
					MVS_CHIP_DISP->stp_reset(mvi,
							phy_no);
				else
					MVS_CHIP_DISP->phy_reset(mvi,
							phy_no, MVS_SOFT_RESET);
				return;
			}
		}
	}

	if (phy->irq_status & PHYEV_COMWAKE) {
		tmp = MVS_CHIP_DISP->read_port_irq_mask(mvi, phy_no);
		MVS_CHIP_DISP->write_port_irq_mask(mvi, phy_no,
					tmp | PHYEV_SIG_FIS);
		if (phy->timer.function == NULL) {
			phy->timer.function = mvs_sig_time_out;
			phy->timer.expires = jiffies + 5*HZ;
			add_timer(&phy->timer);
		}
	}
	if (phy->irq_status & (PHYEV_SIG_FIS | PHYEV_ID_DONE)) {
		phy->phy_status = mvs_is_phy_ready(mvi, phy_no);
		mv_dprintk("notify plug in on phy[%d]\n", phy_no);
		if (phy->phy_status) {
			mdelay(10);
			MVS_CHIP_DISP->detect_porttype(mvi, phy_no);
			if (phy->phy_type & PORT_TYPE_SATA) {
				tmp = MVS_CHIP_DISP->read_port_irq_mask(
						mvi, phy_no);
				tmp &= ~PHYEV_SIG_FIS;
				MVS_CHIP_DISP->write_port_irq_mask(mvi,
							phy_no, tmp);
			}
			mvs_update_phyinfo(mvi, phy_no, 0);
			if (phy->phy_type & PORT_TYPE_SAS) {
				MVS_CHIP_DISP->phy_reset(mvi, phy_no, MVS_PHY_TUNE);
				mdelay(10);
			}

			mvs_bytes_dmaed(mvi, phy_no);
			/* whether driver is going to handle hot plug */
			if (phy->phy_event & PHY_PLUG_OUT) {
				mvs_port_notify_formed(&phy->sas_phy, 0);
				phy->phy_event &= ~PHY_PLUG_OUT;
			}
		} else {
			mv_dprintk("plugin interrupt but phy%d is gone\n",
				phy_no + mvi->id*mvi->chip->n_phy);
		}
	} else if (phy->irq_status & PHYEV_BROAD_CH) {
		mv_dprintk("phy %d broadcast change.\n",
			phy_no + mvi->id*mvi->chip->n_phy);
		mvs_handle_event(mvi, (void *)(unsigned long)phy_no,
				EXP_BRCT_CHG);
	}
}
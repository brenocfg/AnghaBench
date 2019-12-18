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
typedef  void* uint32_t ;
struct sas_phy_linkrates {int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; } ;
struct sas_phy {void* phy_reset_problem_count; void* loss_of_dword_sync_count; void* running_disparity_error_count; void* invalid_dword_count; } ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_phy_event ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct pm8001_phy {int /*<<< orphan*/  phy_attached; int /*<<< orphan*/  sas_phy; int /*<<< orphan*/  phy_state; int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; int /*<<< orphan*/ * enable_completion; } ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  chip_id; TYPE_2__* io_mem; struct sas_ha_struct* sas; struct pm8001_phy* phy; } ;
struct asd_sas_phy {int id; struct sas_phy* phy; TYPE_1__* ha; } ;
typedef  enum phy_func { ____Placeholder_phy_func } phy_func ;
struct TYPE_6__ {int /*<<< orphan*/  (* phy_stop_req ) (struct pm8001_hba_info*,int) ;int /*<<< orphan*/  (* phy_ctl_req ) (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_start_req ) (struct pm8001_hba_info*,int) ;} ;
struct TYPE_5__ {scalar_t__ memvirtaddr; } ;
struct TYPE_4__ {struct pm8001_hba_info* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PHYE_LOSS_OF_SIGNAL ; 
#define  PHY_FUNC_DISABLE 133 
#define  PHY_FUNC_GET_EVENTS 132 
#define  PHY_FUNC_HARD_RESET 131 
#define  PHY_FUNC_LINK_RESET 130 
#define  PHY_FUNC_RELEASE_SPINUP_HOLD 129 
#define  PHY_FUNC_SET_LINK_RATE 128 
 int /*<<< orphan*/  PHY_HARD_RESET ; 
 int /*<<< orphan*/  PHY_LINK_DISABLE ; 
 int /*<<< orphan*/  PHY_LINK_RESET ; 
 int /*<<< orphan*/  PHY_STATE_LINK_UP_SPC ; 
 int /*<<< orphan*/  PHY_STATE_LINK_UP_SPCV ; 
 TYPE_3__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  chip_8001 ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  sas_phy_disconnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub10 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub4 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub6 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int pm8001_phy_control(struct asd_sas_phy *sas_phy, enum phy_func func,
	void *funcdata)
{
	int rc = 0, phy_id = sas_phy->id;
	struct pm8001_hba_info *pm8001_ha = NULL;
	struct sas_phy_linkrates *rates;
	struct sas_ha_struct *sas_ha;
	struct pm8001_phy *phy;
	DECLARE_COMPLETION_ONSTACK(completion);
	unsigned long flags;
	pm8001_ha = sas_phy->ha->lldd_ha;
	phy = &pm8001_ha->phy[phy_id];
	pm8001_ha->phy[phy_id].enable_completion = &completion;
	switch (func) {
	case PHY_FUNC_SET_LINK_RATE:
		rates = funcdata;
		if (rates->minimum_linkrate) {
			pm8001_ha->phy[phy_id].minimum_linkrate =
				rates->minimum_linkrate;
		}
		if (rates->maximum_linkrate) {
			pm8001_ha->phy[phy_id].maximum_linkrate =
				rates->maximum_linkrate;
		}
		if (pm8001_ha->phy[phy_id].phy_state ==  PHY_LINK_DISABLE) {
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			wait_for_completion(&completion);
		}
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		break;
	case PHY_FUNC_HARD_RESET:
		if (pm8001_ha->phy[phy_id].phy_state == PHY_LINK_DISABLE) {
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			wait_for_completion(&completion);
		}
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_HARD_RESET);
		break;
	case PHY_FUNC_LINK_RESET:
		if (pm8001_ha->phy[phy_id].phy_state == PHY_LINK_DISABLE) {
			PM8001_CHIP_DISP->phy_start_req(pm8001_ha, phy_id);
			wait_for_completion(&completion);
		}
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		break;
	case PHY_FUNC_RELEASE_SPINUP_HOLD:
		PM8001_CHIP_DISP->phy_ctl_req(pm8001_ha, phy_id,
					      PHY_LINK_RESET);
		break;
	case PHY_FUNC_DISABLE:
		if (pm8001_ha->chip_id != chip_8001) {
			if (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_LINK_UP_SPCV) {
				sas_ha = pm8001_ha->sas;
				sas_phy_disconnected(&phy->sas_phy);
				sas_ha->notify_phy_event(&phy->sas_phy,
					PHYE_LOSS_OF_SIGNAL);
				phy->phy_attached = 0;
			}
		} else {
			if (pm8001_ha->phy[phy_id].phy_state ==
				PHY_STATE_LINK_UP_SPC) {
				sas_ha = pm8001_ha->sas;
				sas_phy_disconnected(&phy->sas_phy);
				sas_ha->notify_phy_event(&phy->sas_phy,
					PHYE_LOSS_OF_SIGNAL);
				phy->phy_attached = 0;
			}
		}
		PM8001_CHIP_DISP->phy_stop_req(pm8001_ha, phy_id);
		break;
	case PHY_FUNC_GET_EVENTS:
		spin_lock_irqsave(&pm8001_ha->lock, flags);
		if (pm8001_ha->chip_id == chip_8001) {
			if (-1 == pm8001_bar4_shift(pm8001_ha,
					(phy_id < 4) ? 0x30000 : 0x40000)) {
				spin_unlock_irqrestore(&pm8001_ha->lock, flags);
				return -EINVAL;
			}
		}
		{
			struct sas_phy *phy = sas_phy->phy;
			uint32_t *qp = (uint32_t *)(((char *)
				pm8001_ha->io_mem[2].memvirtaddr)
				+ 0x1034 + (0x4000 * (phy_id & 3)));

			phy->invalid_dword_count = qp[0];
			phy->running_disparity_error_count = qp[1];
			phy->loss_of_dword_sync_count = qp[3];
			phy->phy_reset_problem_count = qp[4];
		}
		if (pm8001_ha->chip_id == chip_8001)
			pm8001_bar4_shift(pm8001_ha, 0);
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		return 0;
	default:
		rc = -EOPNOTSUPP;
	}
	msleep(300);
	return rc;
}
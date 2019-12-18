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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_hba {TYPE_1__* hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  sem; scalar_t__ reject_stp_links_msk; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_phys_state ) (struct hisi_hba*) ;int /*<<< orphan*/  (* phys_init ) (struct hisi_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_refresh_port_id (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_rescan_topology (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_reset_init_all_devices (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_terminate_stp_reject (struct hisi_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  scsi_unblock_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_hba*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void hisi_sas_controller_reset_done(struct hisi_hba *hisi_hba)
{
	struct Scsi_Host *shost = hisi_hba->shost;
	u32 state;

	/* Init and wait for PHYs to come up and all libsas event finished. */
	hisi_hba->hw->phys_init(hisi_hba);
	msleep(1000);
	hisi_sas_refresh_port_id(hisi_hba);
	clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);

	if (hisi_hba->reject_stp_links_msk)
		hisi_sas_terminate_stp_reject(hisi_hba);
	hisi_sas_reset_init_all_devices(hisi_hba);
	up(&hisi_hba->sem);
	scsi_unblock_requests(shost);
	clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);

	state = hisi_hba->hw->get_phys_state(hisi_hba);
	hisi_sas_rescan_topology(hisi_hba, state);
}
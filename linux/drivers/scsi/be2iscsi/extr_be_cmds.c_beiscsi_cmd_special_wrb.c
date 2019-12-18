#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct beiscsi_hba {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  pdev; int /*<<< orphan*/  mbox_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  be_dws_cpu_to_le (struct be_mcc_wrb*,int) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct beiscsi_hba* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_cmd_special_wrb(struct be_ctrl_info *ctrl, u32 load)
{
	struct be_mcc_wrb *wrb = wrb_from_mbox(&ctrl->mbox_mem);
	struct beiscsi_hba *phba = pci_get_drvdata(ctrl->pdev);
	u8 *endian_check;
	int status;

	mutex_lock(&ctrl->mbox_lock);
	memset(wrb, 0, sizeof(*wrb));

	endian_check = (u8 *) wrb;
	if (load) {
		/* to start communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0x12;
		*endian_check++ = 0x34;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0x56;
		*endian_check++ = 0x78;
		*endian_check++ = 0xFF;
	} else {
		/* to stop communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0xAA;
		*endian_check++ = 0xBB;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xCC;
		*endian_check++ = 0xDD;
		*endian_check = 0xFF;
	}
	be_dws_cpu_to_le(wrb, sizeof(*wrb));

	status = be_mbox_notify(ctrl);
	if (status)
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BC_%d : special WRB message failed\n");
	mutex_unlock(&ctrl->mbox_lock);
	return status;
}
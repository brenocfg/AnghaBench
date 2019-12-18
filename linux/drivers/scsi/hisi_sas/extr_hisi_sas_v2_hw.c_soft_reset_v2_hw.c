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
typedef  int u32 ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AM_CTRL_GLOBAL ; 
 scalar_t__ AM_CURR_TRANS_RETURN ; 
 scalar_t__ AXI_MASTER_CFG_BASE ; 
 scalar_t__ DLVRY_QUEUE_ENABLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  hisi_sas_init_mem (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_kill_tasklets (struct hisi_hba*) ; 
 int hisi_sas_read32_relaxed (struct hisi_hba*,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_stop_phys (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,int) ; 
 int hw_init_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  interrupt_disable_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  phys_reject_stp_links_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int soft_reset_v2_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int rc, cnt;

	interrupt_disable_v2_hw(hisi_hba);
	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE, 0x0);
	hisi_sas_kill_tasklets(hisi_hba);

	hisi_sas_stop_phys(hisi_hba);

	mdelay(10);

	hisi_sas_write32(hisi_hba, AXI_MASTER_CFG_BASE + AM_CTRL_GLOBAL, 0x1);

	/* wait until bus idle */
	cnt = 0;
	while (1) {
		u32 status = hisi_sas_read32_relaxed(hisi_hba,
				AXI_MASTER_CFG_BASE + AM_CURR_TRANS_RETURN);

		if (status == 0x3)
			break;

		udelay(10);
		if (cnt++ > 10) {
			dev_err(dev, "wait axi bus state to idle timeout!\n");
			return -1;
		}
	}

	hisi_sas_init_mem(hisi_hba);

	rc = hw_init_v2_hw(hisi_hba);
	if (rc)
		return rc;

	phys_reject_stp_links_v2_hw(hisi_hba);

	return 0;
}
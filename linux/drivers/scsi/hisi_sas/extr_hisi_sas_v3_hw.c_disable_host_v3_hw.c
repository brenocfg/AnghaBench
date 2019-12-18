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
 int AM_CTRL_SHUTDOWN_REQ_MSK ; 
 scalar_t__ AM_CURR_TRANS_RETURN ; 
 scalar_t__ AXI_MASTER_CFG_BASE ; 
 scalar_t__ DLVRY_QUEUE_ENABLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  hisi_sas_kill_tasklets (struct hisi_hba*) ; 
 int hisi_sas_read32 (struct hisi_hba*,scalar_t__) ; 
 int hisi_sas_read32_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  hisi_sas_stop_phys (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,scalar_t__,int) ; 
 int /*<<< orphan*/  interrupt_disable_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int disable_host_v3_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	u32 status, reg_val;
	int rc;

	interrupt_disable_v3_hw(hisi_hba);
	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE, 0x0);
	hisi_sas_kill_tasklets(hisi_hba);

	hisi_sas_stop_phys(hisi_hba);

	mdelay(10);

	reg_val = hisi_sas_read32(hisi_hba, AXI_MASTER_CFG_BASE +
				  AM_CTRL_GLOBAL);
	reg_val |= AM_CTRL_SHUTDOWN_REQ_MSK;
	hisi_sas_write32(hisi_hba, AXI_MASTER_CFG_BASE +
			 AM_CTRL_GLOBAL, reg_val);

	/* wait until bus idle */
	rc = hisi_sas_read32_poll_timeout(AXI_MASTER_CFG_BASE +
					  AM_CURR_TRANS_RETURN, status,
					  status == 0x3, 10, 100);
	if (rc) {
		dev_err(dev, "axi bus is not idle, rc=%d\n", rc);
		return rc;
	}

	return 0;
}
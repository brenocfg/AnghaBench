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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int cmd; int resp_needed; int len; void* type; int /*<<< orphan*/  params; } ;
struct TYPE_8__ {TYPE_3__ s; } ;
struct octeon_mbox_cmd {int /*<<< orphan*/ * data; TYPE_4__ msg; } ;
struct octeon_mbox {size_t q_no; struct octeon_device* oct_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dpiring_to_vfpcidev_lut; } ;
struct octeon_device {TYPE_2__* pci_dev; TYPE_1__ sriov_info; int /*<<< orphan*/  pfvf_hsword; } ;
struct oct_vf_stats {int dummy; } ;
struct lio_version {int /*<<< orphan*/  micro; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIQUIDIO_BASE_MAJOR_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MICRO_VERSION ; 
 int /*<<< orphan*/  LIQUIDIO_BASE_MINOR_VERSION ; 
 int /*<<< orphan*/  OCTEON_CN23XX_VF (struct octeon_device*) ; 
#define  OCTEON_GET_VF_STATS 131 
 void* OCTEON_MBOX_RESPONSE ; 
#define  OCTEON_PF_CHANGED_VF_MACADDR 130 
#define  OCTEON_VF_ACTIVE 129 
#define  OCTEON_VF_FLR_REQUEST 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  get_vf_stats (struct octeon_device*,struct oct_vf_stats*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octeon_mbox_write (struct octeon_device*,struct octeon_mbox_cmd*) ; 
 int /*<<< orphan*/  octeon_pf_changed_vf_macaddr (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_flr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int octeon_mbox_process_cmd(struct octeon_mbox *mbox,
				   struct octeon_mbox_cmd *mbox_cmd)
{
	struct octeon_device *oct = mbox->oct_dev;

	switch (mbox_cmd->msg.s.cmd) {
	case OCTEON_VF_ACTIVE:
		dev_dbg(&oct->pci_dev->dev, "got vfactive sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_RESPONSE;
		mbox_cmd->msg.s.resp_needed = 1;
		mbox_cmd->msg.s.len = 2;
		mbox_cmd->data[0] = 0; /* VF version is in mbox_cmd->data[0] */
		((struct lio_version *)&mbox_cmd->data[0])->major =
			LIQUIDIO_BASE_MAJOR_VERSION;
		((struct lio_version *)&mbox_cmd->data[0])->minor =
			LIQUIDIO_BASE_MINOR_VERSION;
		((struct lio_version *)&mbox_cmd->data[0])->micro =
			LIQUIDIO_BASE_MICRO_VERSION;
		memcpy(mbox_cmd->msg.s.params, (uint8_t *)&oct->pfvf_hsword, 6);
		/* Sending core cofig info to the corresponding active VF.*/
		octeon_mbox_write(oct, mbox_cmd);
		break;

	case OCTEON_VF_FLR_REQUEST:
		dev_info(&oct->pci_dev->dev,
			 "got a request for FLR from VF that owns DPI ring %u\n",
			 mbox->q_no);
		pcie_flr(oct->sriov_info.dpiring_to_vfpcidev_lut[mbox->q_no]);
		break;

	case OCTEON_PF_CHANGED_VF_MACADDR:
		if (OCTEON_CN23XX_VF(oct))
			octeon_pf_changed_vf_macaddr(oct,
						     mbox_cmd->msg.s.params);
		break;

	case OCTEON_GET_VF_STATS:
		dev_dbg(&oct->pci_dev->dev, "Got VF stats request. Sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_RESPONSE;
		mbox_cmd->msg.s.resp_needed = 1;
		mbox_cmd->msg.s.len = 1 +
			sizeof(struct oct_vf_stats) / sizeof(u64);
		get_vf_stats(oct, (struct oct_vf_stats *)mbox_cmd->data);
		octeon_mbox_write(oct, mbox_cmd);
		break;
	default:
		break;
	}
	return 0;
}
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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct hwrm_queue_pri2cos_qcfg_output {int pri0_cos_queue_id; scalar_t__ queue_cfg_info; } ;
struct hwrm_queue_pri2cos_qcfg_input {int /*<<< orphan*/  port_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct bnxt_re_dev {struct bnxt_en_dev* en_dev; int /*<<< orphan*/  netdev; } ;
struct bnxt_fw_msg {int dummy; } ;
struct bnxt_en_dev {TYPE_2__* en_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct bnxt {TYPE_1__ pf; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  fw_msg ;
struct TYPE_4__ {int (* bnxt_send_fw_msg ) (struct bnxt_en_dev*,int /*<<< orphan*/ ,struct bnxt_fw_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int /*<<< orphan*/  DFLT_HWRM_CMD_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HWRM_QUEUE_PRI2COS_QCFG ; 
 int HWRM_QUEUE_PRI2COS_QCFG_INPUT_FLAGS_IVLAN ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  bnxt_re_fill_fw_msg (struct bnxt_fw_msg*,void*,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_init_hwrm_hdr (struct bnxt_re_dev*,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct bnxt_fw_msg*,int /*<<< orphan*/ ,int) ; 
 struct bnxt* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 int stub1 (struct bnxt_en_dev*,int /*<<< orphan*/ ,struct bnxt_fw_msg*) ; 

__attribute__((used)) static int bnxt_re_query_hwrm_pri2cos(struct bnxt_re_dev *rdev, u8 dir,
				      u64 *cid_map)
{
	struct hwrm_queue_pri2cos_qcfg_input req = {0};
	struct bnxt *bp = netdev_priv(rdev->netdev);
	struct hwrm_queue_pri2cos_qcfg_output resp;
	struct bnxt_en_dev *en_dev = rdev->en_dev;
	struct bnxt_fw_msg fw_msg;
	u32 flags = 0;
	u8 *qcfgmap, *tmp_map;
	int rc = 0, i;

	if (!cid_map)
		return -EINVAL;

	memset(&fw_msg, 0, sizeof(fw_msg));
	bnxt_re_init_hwrm_hdr(rdev, (void *)&req,
			      HWRM_QUEUE_PRI2COS_QCFG, -1, -1);
	flags |= (dir & 0x01);
	flags |= HWRM_QUEUE_PRI2COS_QCFG_INPUT_FLAGS_IVLAN;
	req.flags = cpu_to_le32(flags);
	req.port_id = bp->pf.port_id;

	bnxt_re_fill_fw_msg(&fw_msg, (void *)&req, sizeof(req), (void *)&resp,
			    sizeof(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	if (rc)
		return rc;

	if (resp.queue_cfg_info) {
		dev_warn(rdev_to_dev(rdev),
			 "Asymmetric cos queue configuration detected");
		dev_warn(rdev_to_dev(rdev),
			 " on device, QoS may not be fully functional\n");
	}
	qcfgmap = &resp.pri0_cos_queue_id;
	tmp_map = (u8 *)cid_map;
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		tmp_map[i] = qcfgmap[i];

	return rc;
}
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
typedef  int u64 ;
struct hwrm_ver_get_output {int hwrm_intf_patch; scalar_t__ hwrm_intf_build; scalar_t__ hwrm_intf_minor; scalar_t__ hwrm_intf_major; int /*<<< orphan*/  member_0; } ;
struct hwrm_ver_get_input {int /*<<< orphan*/  hwrm_intf_upd; int /*<<< orphan*/  hwrm_intf_min; int /*<<< orphan*/  hwrm_intf_maj; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int hwrm_intf_ver; } ;
struct bnxt_re_dev {TYPE_2__ qplib_ctx; struct bnxt_en_dev* en_dev; } ;
struct bnxt_fw_msg {int dummy; } ;
struct bnxt_en_dev {TYPE_1__* en_ops; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  fw_msg ;
struct TYPE_3__ {int (* bnxt_send_fw_msg ) (struct bnxt_en_dev*,int /*<<< orphan*/ ,struct bnxt_fw_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int /*<<< orphan*/  DFLT_HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VERSION_MAJOR ; 
 int /*<<< orphan*/  HWRM_VERSION_MINOR ; 
 int /*<<< orphan*/  HWRM_VERSION_UPDATE ; 
 int /*<<< orphan*/  HWRM_VER_GET ; 
 int /*<<< orphan*/  bnxt_re_fill_fw_msg (struct bnxt_fw_msg*,void*,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_init_hwrm_hdr (struct bnxt_re_dev*,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct bnxt_fw_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 
 int stub1 (struct bnxt_en_dev*,int /*<<< orphan*/ ,struct bnxt_fw_msg*) ; 

__attribute__((used)) static void bnxt_re_query_hwrm_intf_version(struct bnxt_re_dev *rdev)
{
	struct bnxt_en_dev *en_dev = rdev->en_dev;
	struct hwrm_ver_get_output resp = {0};
	struct hwrm_ver_get_input req = {0};
	struct bnxt_fw_msg fw_msg;
	int rc = 0;

	memset(&fw_msg, 0, sizeof(fw_msg));
	bnxt_re_init_hwrm_hdr(rdev, (void *)&req,
			      HWRM_VER_GET, -1, -1);
	req.hwrm_intf_maj = HWRM_VERSION_MAJOR;
	req.hwrm_intf_min = HWRM_VERSION_MINOR;
	req.hwrm_intf_upd = HWRM_VERSION_UPDATE;
	bnxt_re_fill_fw_msg(&fw_msg, (void *)&req, sizeof(req), (void *)&resp,
			    sizeof(resp), DFLT_HWRM_CMD_TIMEOUT);
	rc = en_dev->en_ops->bnxt_send_fw_msg(en_dev, BNXT_ROCE_ULP, &fw_msg);
	if (rc) {
		dev_err(rdev_to_dev(rdev),
			"Failed to query HW version, rc = 0x%x", rc);
		return;
	}
	rdev->qplib_ctx.hwrm_intf_ver =
		(u64)resp.hwrm_intf_major << 48 |
		(u64)resp.hwrm_intf_minor << 32 |
		(u64)resp.hwrm_intf_build << 16 |
		resp.hwrm_intf_patch;
}
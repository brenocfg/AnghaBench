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
union qed_mfw_tlv_data {int /*<<< orphan*/  iscsi; int /*<<< orphan*/  fcoe; int /*<<< orphan*/  eth; int /*<<< orphan*/  generic; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct TYPE_2__ {struct qed_common_cb_ops* common; } ;
struct qed_dev {int /*<<< orphan*/  ops_cookie; TYPE_1__ protocol_ops; } ;
struct qed_common_cb_ops {int /*<<< orphan*/  (* get_protocol_tlv_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  get_generic_tlv_data; } ;
typedef  enum qed_mfw_tlv_type { ____Placeholder_qed_mfw_tlv_type } qed_mfw_tlv_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
#define  QED_MFW_TLV_ETH 131 
#define  QED_MFW_TLV_FCOE 130 
#define  QED_MFW_TLV_GENERIC 129 
#define  QED_MFW_TLV_ISCSI 128 
 int /*<<< orphan*/  qed_fill_generic_tlv_data (struct qed_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_mfw_fill_tlv_data(struct qed_hwfn *hwfn, enum qed_mfw_tlv_type type,
			  union qed_mfw_tlv_data *tlv_buf)
{
	struct qed_dev *cdev = hwfn->cdev;
	struct qed_common_cb_ops *ops;

	ops = cdev->protocol_ops.common;
	if (!ops || !ops->get_protocol_tlv_data || !ops->get_generic_tlv_data) {
		DP_NOTICE(hwfn, "Can't collect TLV management info\n");
		return -EINVAL;
	}

	switch (type) {
	case QED_MFW_TLV_GENERIC:
		qed_fill_generic_tlv_data(hwfn->cdev, &tlv_buf->generic);
		break;
	case QED_MFW_TLV_ETH:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->eth);
		break;
	case QED_MFW_TLV_FCOE:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->fcoe);
		break;
	case QED_MFW_TLV_ISCSI:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->iscsi);
		break;
	default:
		break;
	}

	return 0;
}
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
struct hnae3_knic_private_info {int /*<<< orphan*/ * dcb_ops; } ;
struct TYPE_2__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {scalar_t__ vport_id; TYPE_1__ nic; } ;
struct hclge_dev {int dcbx_cap; struct hclge_vport* vport; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_HOST ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 
 int /*<<< orphan*/  hns3_dcb_ops ; 

void hclge_dcb_ops_set(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	struct hnae3_knic_private_info *kinfo;

	/* Hdev does not support DCB or vport is
	 * not a pf, then dcb_ops is not set.
	 */
	if (!hnae3_dev_dcb_supported(hdev) ||
	    vport->vport_id != 0)
		return;

	kinfo = &vport->nic.kinfo;
	kinfo->dcb_ops = &hns3_dcb_ops;
	hdev->dcbx_cap = DCB_CAP_DCBX_VER_IEEE | DCB_CAP_DCBX_HOST;
}
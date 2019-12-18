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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int HCLGE_FLAG_DCB_ENABLE ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 int hclge_client_setup_tc (struct hclge_dev*) ; 
 int hclge_dcb_common_validate (struct hclge_dev*,int,int*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_notify_down_uinit (struct hclge_dev*) ; 
 int hclge_notify_init_up (struct hclge_dev*) ; 
 int hclge_tm_init_hw (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_tm_prio_tc_info_update (struct hclge_dev*,int*) ; 
 int /*<<< orphan*/  hclge_tm_schd_info_update (struct hclge_dev*,int) ; 

__attribute__((used)) static int hclge_setup_tc(struct hnae3_handle *h, u8 tc, u8 *prio_tc)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;
	int ret;

	if (hdev->flag & HCLGE_FLAG_DCB_ENABLE)
		return -EINVAL;

	ret = hclge_dcb_common_validate(hdev, tc, prio_tc);
	if (ret)
		return -EINVAL;

	ret = hclge_notify_down_uinit(hdev);
	if (ret)
		return ret;

	hclge_tm_schd_info_update(hdev, tc);
	hclge_tm_prio_tc_info_update(hdev, prio_tc);

	ret = hclge_tm_init_hw(hdev, false);
	if (ret)
		goto err_out;

	ret = hclge_client_setup_tc(hdev);
	if (ret)
		goto err_out;

	hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;

	if (tc > 1)
		hdev->flag |= HCLGE_FLAG_MQPRIO_ENABLE;
	else
		hdev->flag &= ~HCLGE_FLAG_MQPRIO_ENABLE;

	return hclge_notify_init_up(hdev);

err_out:
	hclge_notify_init_up(hdev);

	return ret;
}
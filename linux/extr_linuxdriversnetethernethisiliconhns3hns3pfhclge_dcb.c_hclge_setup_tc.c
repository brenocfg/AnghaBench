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
typedef  scalar_t__ u8 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int flag; scalar_t__ tc_max; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HCLGE_FLAG_DCB_ENABLE ; 
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_tm_init_hw (struct hclge_dev*) ; 
 int hclge_tm_prio_tc_info_update (struct hclge_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  hclge_tm_schd_info_update (struct hclge_dev*,scalar_t__) ; 

__attribute__((used)) static int hclge_setup_tc(struct hnae3_handle *h, u8 tc, u8 *prio_tc)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;
	int ret;

	if (hdev->flag & HCLGE_FLAG_DCB_ENABLE)
		return -EINVAL;

	if (tc > hdev->tc_max) {
		dev_err(&hdev->pdev->dev,
			"setup tc failed, tc(%u) > tc_max(%u)\n",
			tc, hdev->tc_max);
		return -EINVAL;
	}

	hclge_tm_schd_info_update(hdev, tc);

	ret = hclge_tm_prio_tc_info_update(hdev, prio_tc);
	if (ret)
		return ret;

	ret = hclge_tm_init_hw(hdev);
	if (ret)
		return ret;

	hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;

	if (tc > 1)
		hdev->flag |= HCLGE_FLAG_MQPRIO_ENABLE;
	else
		hdev->flag &= ~HCLGE_FLAG_MQPRIO_ENABLE;

	return 0;
}
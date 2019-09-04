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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  HNAE3_MAC_INTER_LOOP_MAC 129 
#define  HNAE3_MAC_INTER_LOOP_SERDES 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_mac_loopback (struct hclge_dev*,int) ; 
 int hclge_set_serdes_loopback (struct hclge_dev*,int) ; 

__attribute__((used)) static int hclge_set_loopback(struct hnae3_handle *handle,
			      enum hnae3_loop loop_mode, bool en)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int ret;

	switch (loop_mode) {
	case HNAE3_MAC_INTER_LOOP_MAC:
		ret = hclge_set_mac_loopback(hdev, en);
		break;
	case HNAE3_MAC_INTER_LOOP_SERDES:
		ret = hclge_set_serdes_loopback(hdev, en);
		break;
	default:
		ret = -ENOTSUPP;
		dev_err(&hdev->pdev->dev,
			"loop_mode %d is not supported\n", loop_mode);
		break;
	}

	return ret;
}
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
struct hclge_dev {int reset_type; } ;

/* Variables and functions */
#define  HNAE3_FLR_RESET 129 
#define  HNAE3_FUNC_RESET 128 
 int hclge_set_all_vf_rst (struct hclge_dev*,int) ; 

__attribute__((used)) static int hclge_reset_prepare_down(struct hclge_dev *hdev)
{
	int ret = 0;

	switch (hdev->reset_type) {
	case HNAE3_FUNC_RESET:
		/* fall through */
	case HNAE3_FLR_RESET:
		ret = hclge_set_all_vf_rst(hdev, true);
		break;
	default:
		break;
	}

	return ret;
}
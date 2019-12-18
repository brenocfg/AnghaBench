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
#define  HNAE3_FLR_RESET 131 
#define  HNAE3_FUNC_RESET 130 
#define  HNAE3_GLOBAL_RESET 129 
#define  HNAE3_IMP_RESET 128 
 int /*<<< orphan*/  hclge_reset_handshake (struct hclge_dev*,int) ; 
 int hclge_set_all_vf_rst (struct hclge_dev*,int) ; 
 int hclge_set_rst_done (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_reset_prepare_up(struct hclge_dev *hdev)
{
	int ret = 0;

	switch (hdev->reset_type) {
	case HNAE3_FUNC_RESET:
		/* fall through */
	case HNAE3_FLR_RESET:
		ret = hclge_set_all_vf_rst(hdev, false);
		break;
	case HNAE3_GLOBAL_RESET:
		/* fall through */
	case HNAE3_IMP_RESET:
		ret = hclge_set_rst_done(hdev);
		break;
	default:
		break;
	}

	/* clear up the handshake status after re-initialize done */
	hclge_reset_handshake(hdev, false);

	return ret;
}
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
struct hclge_mac {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {struct hclge_mac mac; } ;
struct hclge_dev {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_DEFAULT_PAUSE_TRANS_GAP ; 
 int /*<<< orphan*/  HCLGE_DEFAULT_PAUSE_TRANS_TIME ; 
 int hclge_pause_param_cfg (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_pause_param_setup_hw(struct hclge_dev *hdev)
{
	struct hclge_mac *mac = &hdev->hw.mac;

	return hclge_pause_param_cfg(hdev, mac->mac_addr,
				     HCLGE_DEFAULT_PAUSE_TRANS_GAP,
				     HCLGE_DEFAULT_PAUSE_TRANS_TIME);
}
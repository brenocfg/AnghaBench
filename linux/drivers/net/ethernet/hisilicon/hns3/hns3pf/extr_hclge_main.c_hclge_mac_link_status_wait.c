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
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HCLGE_LINK_STATUS_MS ; 
 int HCLGE_MAC_LINK_STATUS_NUM ; 
 int hclge_get_mac_link_status (struct hclge_dev*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_mac_link_status_wait(struct hclge_dev *hdev, int link_ret)
{
#define HCLGE_MAC_LINK_STATUS_NUM  100

	int i = 0;
	int ret;

	do {
		ret = hclge_get_mac_link_status(hdev);
		if (ret < 0)
			return ret;
		else if (ret == link_ret)
			return 0;

		msleep(HCLGE_LINK_STATUS_MS);
	} while (++i < HCLGE_MAC_LINK_STATUS_NUM);
	return -EBUSY;
}
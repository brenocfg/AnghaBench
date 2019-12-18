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
 int /*<<< orphan*/  HNAE3_LOOP_PARALLEL_SERDES ; 
 int /*<<< orphan*/  HNAE3_LOOP_SERIAL_SERDES ; 
 int hclge_cfg_serdes_loopback (struct hclge_dev*,int,int /*<<< orphan*/ ) ; 
 int hclge_set_app_loopback (struct hclge_dev*,int) ; 

__attribute__((used)) static int hclge_set_default_loopback(struct hclge_dev *hdev)
{
	int ret;

	ret = hclge_set_app_loopback(hdev, false);
	if (ret)
		return ret;

	ret = hclge_cfg_serdes_loopback(hdev, false, HNAE3_LOOP_SERIAL_SERDES);
	if (ret)
		return ret;

	return hclge_cfg_serdes_loopback(hdev, false,
					 HNAE3_LOOP_PARALLEL_SERDES);
}
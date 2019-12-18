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
 int /*<<< orphan*/  HCLGE_PPP_CMD0_INT_CMD ; 
 int /*<<< orphan*/  HCLGE_PPP_CMD1_INT_CMD ; 
 int hclge_config_ppp_error_interrupt (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_config_ppp_hw_err_int(struct hclge_dev *hdev, bool en)
{
	int ret;

	ret = hclge_config_ppp_error_interrupt(hdev, HCLGE_PPP_CMD0_INT_CMD,
					       en);
	if (ret)
		return ret;

	ret = hclge_config_ppp_error_interrupt(hdev, HCLGE_PPP_CMD1_INT_CMD,
					       en);

	return ret;
}
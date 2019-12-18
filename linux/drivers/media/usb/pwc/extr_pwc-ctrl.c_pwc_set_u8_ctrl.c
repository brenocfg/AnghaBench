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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pwc_device {int /*<<< orphan*/ * ctrl_buf; } ;

/* Variables and functions */
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int pwc_set_u8_ctrl(struct pwc_device *pdev, u8 request, u16 value, u8 data)
{
	int ret;

	pdev->ctrl_buf[0] = data;
	ret = send_control_msg(pdev, request, value, pdev->ctrl_buf, 1);
	if (ret < 0)
		return ret;

	return 0;
}
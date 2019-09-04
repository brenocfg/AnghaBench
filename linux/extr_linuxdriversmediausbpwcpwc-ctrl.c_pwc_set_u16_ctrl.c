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
typedef  int u16 ;
struct pwc_device {int* ctrl_buf; } ;

/* Variables and functions */
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int,int*,int) ; 

int pwc_set_u16_ctrl(struct pwc_device *pdev, u8 request, u16 value, u16 data)
{
	int ret;

	pdev->ctrl_buf[0] = data & 0xff;
	pdev->ctrl_buf[1] = data >> 8;
	ret = send_control_msg(pdev, request, value, pdev->ctrl_buf, 2);
	if (ret < 0)
		return ret;

	return 0;
}
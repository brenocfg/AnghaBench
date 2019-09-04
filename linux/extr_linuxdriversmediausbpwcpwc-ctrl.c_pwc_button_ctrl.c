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
typedef  int /*<<< orphan*/  u16 ;
struct pwc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_STATUS_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pwc_button_ctrl(struct pwc_device *pdev, u16 value)
{
	int ret;

	ret = send_control_msg(pdev, SET_STATUS_CTL, value, NULL, 0);
	if (ret < 0)
		return ret;

	return 0;
}
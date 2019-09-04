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
struct pwc_device {int type; int release; int* ctrl_buf; int /*<<< orphan*/  power_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWC_ERROR (char*,char*,int) ; 
 int /*<<< orphan*/  SET_POWER_SAVE_MODE_FORMATTER ; 
 int /*<<< orphan*/  SET_STATUS_CTL ; 
 int send_control_msg (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void pwc_camera_power(struct pwc_device *pdev, int power)
{
	int r;

	if (!pdev->power_save)
		return;

	if (pdev->type < 675 || (pdev->type < 730 && pdev->release < 6))
		return;	/* Not supported by Nala or Timon < release 6 */

	if (power)
		pdev->ctrl_buf[0] = 0x00; /* active */
	else
		pdev->ctrl_buf[0] = 0xFF; /* power save */
	r = send_control_msg(pdev, SET_STATUS_CTL,
		SET_POWER_SAVE_MODE_FORMATTER, pdev->ctrl_buf, 1);
	if (r < 0)
		PWC_ERROR("Failed to power %s camera (%d)\n",
			  power ? "on" : "off", r);
}
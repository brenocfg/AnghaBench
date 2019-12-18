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
struct us_data {int /*<<< orphan*/  send_ctrl_pipe; } ;

/* Variables and functions */
 unsigned char ALAUDA_ACK_SM_MEDIA_CHANGE ; 
 unsigned char ALAUDA_ACK_XD_MEDIA_CHANGE ; 
 scalar_t__ ALAUDA_PORT_XD ; 
 scalar_t__ MEDIA_PORT (struct us_data*) ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alauda_ack_media(struct us_data *us)
{
	unsigned char command;

	if (MEDIA_PORT(us) == ALAUDA_PORT_XD)
		command = ALAUDA_ACK_XD_MEDIA_CHANGE;
	else
		command = ALAUDA_ACK_SM_MEDIA_CHANGE;

	return usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
		command, 0x40, 0, 1, NULL, 0);
}
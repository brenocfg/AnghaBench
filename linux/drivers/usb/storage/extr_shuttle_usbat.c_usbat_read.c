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
struct us_data {int /*<<< orphan*/  recv_ctrl_pipe; } ;

/* Variables and functions */
 unsigned char USBAT_CMD_READ_REG ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int usbat_read(struct us_data *us,
		      unsigned char access,
		      unsigned char reg,
		      unsigned char *content)
{
	return usb_stor_ctrl_transfer(us,
		us->recv_ctrl_pipe,
		access | USBAT_CMD_READ_REG,
		0xC0,
		(u16)reg,
		0,
		content,
		1);
}
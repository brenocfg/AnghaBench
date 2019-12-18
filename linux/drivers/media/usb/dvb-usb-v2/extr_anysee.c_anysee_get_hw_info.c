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
struct dvb_usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_HW_INFO ; 
 int anysee_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int anysee_get_hw_info(struct dvb_usb_device *d, u8 *id)
{
	u8 buf[] = {CMD_GET_HW_INFO};
	return anysee_ctrl_msg(d, buf, sizeof(buf), id, 3);
}
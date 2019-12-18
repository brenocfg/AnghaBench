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
struct dvb_usb_device {int dummy; } ;
struct dvb_ca_en50221 {struct dvb_usb_device* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IOD ; 
 int anysee_wr_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int anysee_ci_slot_ts_enable(struct dvb_ca_en50221 *ci, int slot)
{
	struct dvb_usb_device *d = ci->data;
	int ret;

	ret = anysee_wr_reg_mask(d, REG_IOD, (0 << 1), 0x02);
	if (ret)
		return ret;

	return 0;
}
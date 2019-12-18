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
struct anysee_state {scalar_t__ ci_cam_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IOA ; 
 int anysee_wr_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int) ; 
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int anysee_ci_slot_reset(struct dvb_ca_en50221 *ci, int slot)
{
	struct dvb_usb_device *d = ci->data;
	int ret;
	struct anysee_state *state = d_to_priv(d);

	state->ci_cam_ready = jiffies + msecs_to_jiffies(1000);

	ret = anysee_wr_reg_mask(d, REG_IOA, (0 << 7), 0x80);
	if (ret)
		return ret;

	msleep(300);

	ret = anysee_wr_reg_mask(d, REG_IOA, (1 << 7), 0x80);
	if (ret)
		return ret;

	return 0;
}
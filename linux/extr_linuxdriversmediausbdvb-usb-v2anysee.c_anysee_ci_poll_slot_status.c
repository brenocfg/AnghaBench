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
typedef  scalar_t__ u8 ;
struct dvb_usb_device {int dummy; } ;
struct dvb_ca_en50221 {struct dvb_usb_device* data; } ;
struct anysee_state {int /*<<< orphan*/  ci_cam_ready; } ;

/* Variables and functions */
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int /*<<< orphan*/  REG_IOC ; 
 int anysee_rd_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anysee_ci_poll_slot_status(struct dvb_ca_en50221 *ci, int slot,
	int open)
{
	struct dvb_usb_device *d = ci->data;
	struct anysee_state *state = d_to_priv(d);
	int ret;
	u8 tmp = 0;

	ret = anysee_rd_reg_mask(d, REG_IOC, &tmp, 0x40);
	if (ret)
		return ret;

	if (tmp == 0) {
		ret = DVB_CA_EN50221_POLL_CAM_PRESENT;
		if (time_after(jiffies, state->ci_cam_ready))
			ret |= DVB_CA_EN50221_POLL_CAM_READY;
	}

	return ret;
}
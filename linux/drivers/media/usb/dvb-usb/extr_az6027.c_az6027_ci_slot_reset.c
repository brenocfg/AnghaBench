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
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_device {scalar_t__ priv; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct az6027_device_state {int /*<<< orphan*/  ca_mutex; } ;

/* Variables and functions */
 scalar_t__ CI_CamReady (struct dvb_ca_en50221*,int) ; 
 int az6027_usb_out_op (struct dvb_usb_device*,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int az6027_ci_slot_reset(struct dvb_ca_en50221 *ca, int slot)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6027_device_state *state = (struct az6027_device_state *)d->priv;

	int ret, i;
	u8 req;
	u16 value;
	u16 index;
	int blen;

	mutex_lock(&state->ca_mutex);

	req = 0xC6;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value, index, NULL, blen);
	if (ret != 0) {
		warn("usb out operation failed. (%d)", ret);
		goto failed;
	}

	msleep(500);
	req = 0xC6;
	value = 0;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value, index, NULL, blen);
	if (ret != 0) {
		warn("usb out operation failed. (%d)", ret);
		goto failed;
	}

	for (i = 0; i < 15; i++) {
		msleep(100);

		if (CI_CamReady(ca, slot)) {
			deb_info("CAM Ready");
			break;
		}
	}
	msleep(5000);

failed:
	mutex_unlock(&state->ca_mutex);
	return ret;
}
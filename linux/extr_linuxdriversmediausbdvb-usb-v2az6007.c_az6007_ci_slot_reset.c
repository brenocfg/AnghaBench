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
struct dvb_usb_device {int dummy; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct az6007_device_state {int /*<<< orphan*/  ca_mutex; } ;

/* Variables and functions */
 scalar_t__ CI_CamReady (struct dvb_ca_en50221*,int) ; 
 int az6007_write (struct dvb_usb_device*,int,int,int,int /*<<< orphan*/ *,int) ; 
 struct az6007_device_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int az6007_ci_slot_reset(struct dvb_ca_en50221 *ca, int slot)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);

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

	ret = az6007_write(d, req, value, index, NULL, blen);
	if (ret != 0) {
		pr_warn("usb out operation failed. (%d)\n", ret);
		goto failed;
	}

	msleep(500);
	req = 0xC6;
	value = 0;
	index = 0;
	blen = 0;

	ret = az6007_write(d, req, value, index, NULL, blen);
	if (ret != 0) {
		pr_warn("usb out operation failed. (%d)\n", ret);
		goto failed;
	}

	for (i = 0; i < 15; i++) {
		msleep(100);

		if (CI_CamReady(ca, slot)) {
			pr_debug("CAM Ready\n");
			break;
		}
	}
	msleep(5000);

failed:
	mutex_unlock(&state->ca_mutex);
	return ret;
}
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
 int EINVAL ; 
 int az6007_write (struct dvb_usb_device*,int,int,int,int /*<<< orphan*/ *,int) ; 
 struct az6007_device_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int az6007_ci_write_cam_control(struct dvb_ca_en50221 *ca,
				       int slot,
				       u8 address,
				       u8 value)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);

	int ret;
	u8 req;
	u16 value1;
	u16 index;
	int blen;

	if (slot != 0)
		return -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC4;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6007_write(d, req, value1, index, NULL, blen);
	if (ret != 0) {
		pr_warn("usb out operation failed. (%d)\n", ret);
		goto failed;
	}

failed:
	mutex_unlock(&state->ca_mutex);
	return ret;
}
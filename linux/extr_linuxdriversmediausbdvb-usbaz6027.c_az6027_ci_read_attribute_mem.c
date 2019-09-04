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
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int az6027_usb_in_op (struct dvb_usb_device*,int,int,int,int*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int az6027_ci_read_attribute_mem(struct dvb_ca_en50221 *ca,
					int slot,
					int address)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6027_device_state *state = (struct az6027_device_state *)d->priv;

	int ret;
	u8 req;
	u16 value;
	u16 index;
	int blen;
	u8 *b;

	if (slot != 0)
		return -EINVAL;

	b = kmalloc(12, GFP_KERNEL);
	if (!b)
		return -ENOMEM;

	mutex_lock(&state->ca_mutex);

	req = 0xC1;
	value = address;
	index = 0;
	blen = 1;

	ret = az6027_usb_in_op(d, req, value, index, b, blen);
	if (ret < 0) {
		warn("usb in operation failed. (%d)", ret);
		ret = -EINVAL;
	} else {
		ret = b[0];
	}

	mutex_unlock(&state->ca_mutex);
	kfree(b);
	return ret;
}
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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int az6007_read (struct dvb_usb_device*,int,int,int,int*,int) ; 
 struct az6007_device_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static int az6007_ci_read_cam_control(struct dvb_ca_en50221 *ca,
				      int slot,
				      u8 address)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);

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

	req = 0xC3;
	value = address;
	index = 0;
	blen = 2;

	ret = az6007_read(d, req, value, index, b, blen);
	if (ret < 0) {
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EINVAL;
	} else {
		if (b[0] == 0)
			pr_warn("Read CI IO error\n");

		ret = b[1];
		pr_debug("read cam data = %x from 0x%x\n", b[1], value);
	}

	mutex_unlock(&state->ca_mutex);
	kfree(b);
	return ret;
}
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
typedef  scalar_t__ u16 ;
struct dvb_usb_device {int dummy; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct az6007_device_state {int /*<<< orphan*/  ca_mutex; } ;

/* Variables and functions */
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int az6007_read (struct dvb_usb_device*,int,scalar_t__,scalar_t__,int*,int) ; 
 struct az6007_device_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int az6007_ci_poll_slot_status(struct dvb_ca_en50221 *ca, int slot, int open)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);
	int ret;
	u8 req;
	u16 value;
	u16 index;
	int blen;
	u8 *b;

	b = kmalloc(12, GFP_KERNEL);
	if (!b)
		return -ENOMEM;
	mutex_lock(&state->ca_mutex);

	req = 0xC5;
	value = 0;
	index = 0;
	blen = 1;

	ret = az6007_read(d, req, value, index, b, blen);
	if (ret < 0) {
		pr_warn("usb in operation failed. (%d)\n", ret);
		ret = -EIO;
	} else
		ret = 0;

	if (!ret && b[0] == 1) {
		ret = DVB_CA_EN50221_POLL_CAM_PRESENT |
		      DVB_CA_EN50221_POLL_CAM_READY;
	}

	mutex_unlock(&state->ca_mutex);
	kfree(b);
	return ret;
}
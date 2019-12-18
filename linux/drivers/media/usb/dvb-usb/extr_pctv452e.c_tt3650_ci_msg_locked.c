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
struct pctv452e_state {int /*<<< orphan*/  ca_mutex; } ;
struct dvb_usb_device {scalar_t__ priv; } ;
struct dvb_ca_en50221 {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tt3650_ci_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int tt3650_ci_msg_locked(struct dvb_ca_en50221 *ca,
				u8 cmd, u8 *data, unsigned int write_len,
				unsigned int read_len)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct pctv452e_state *state = (struct pctv452e_state *)d->priv;
	int ret;

	mutex_lock(&state->ca_mutex);
	ret = tt3650_ci_msg(d, cmd, data, write_len, read_len);
	mutex_unlock(&state->ca_mutex);

	return ret;
}
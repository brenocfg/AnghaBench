#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct vp702x_device_state {int* buf; int /*<<< orphan*/  buf_mutex; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct TYPE_2__ {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vp702x_usb_in_op (TYPE_1__*,int,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vp702x_set_pld_state(struct dvb_usb_adapter *adap, u8 state)
{
	int ret;
	struct vp702x_device_state *st = adap->dev->priv;
	u8 *buf;

	mutex_lock(&st->buf_mutex);

	buf = st->buf;
	memset(buf, 0, 16);
	ret = vp702x_usb_in_op(adap->dev, 0xe0, (state << 8) | 0x0f,
			0, buf, 16);

	mutex_unlock(&st->buf_mutex);

	return ret;
}
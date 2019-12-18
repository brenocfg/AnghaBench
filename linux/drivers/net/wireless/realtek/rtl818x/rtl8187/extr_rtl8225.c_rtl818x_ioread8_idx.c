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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct rtl8187_priv {int /*<<< orphan*/  io_mutex; TYPE_1__* io_dmabuf; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int bits8; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RTL8187_REQT_READ ; 
 int /*<<< orphan*/  RTL8187_REQ_GET_REG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 rtl818x_ioread8_idx(struct rtl8187_priv *priv,
				u8 *addr, u8 idx)
{
	u8 val;

	mutex_lock(&priv->io_mutex);
	usb_control_msg(priv->udev, usb_rcvctrlpipe(priv->udev, 0),
			RTL8187_REQ_GET_REG, RTL8187_REQT_READ,
			(unsigned long)addr, idx & 0x03,
			&priv->io_dmabuf->bits8, sizeof(val), HZ / 2);

	val = priv->io_dmabuf->bits8;
	mutex_unlock(&priv->io_mutex);

	return val;
}
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
typedef  int u16 ;
struct vnt_private {int /*<<< orphan*/  usb_lock; int /*<<< orphan*/  usb; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_FLAGS_DISCONNECTED ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTL_WAIT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vnt_control_in(struct vnt_private *priv, u8 request, u16 value,
		   u16 index, u16 length, u8 *buffer)
{
	int ret = 0;
	u8 *usb_buffer;

	if (test_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags)) {
		ret = -EINVAL;
		goto end;
	}

	mutex_lock(&priv->usb_lock);

	usb_buffer = kmalloc(length, GFP_KERNEL);
	if (!usb_buffer) {
		ret = -ENOMEM;
		goto end_unlock;
	}

	ret = usb_control_msg(priv->usb,
			      usb_rcvctrlpipe(priv->usb, 0),
			      request, 0xc0, value,
			      index, usb_buffer, length, USB_CTL_WAIT);

	if (ret == length)
		memcpy(buffer, usb_buffer, length);

	kfree(usb_buffer);

	if (ret >= 0 && ret < (int)length)
		ret = -EIO;

end_unlock:
	mutex_unlock(&priv->usb_lock);
end:
	return ret;
}
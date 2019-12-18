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
struct vb2_queue {scalar_t__ type; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct hackrf_dev {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  flags; struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_TRANSCEIVER_MODE ; 
 int /*<<< orphan*/  RX_ON ; 
 int /*<<< orphan*/  TX_ON ; 
 scalar_t__ V4L2_BUF_TYPE_SDR_CAPTURE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hackrf_ctrl_msg (struct hackrf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hackrf_free_stream_bufs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_free_urbs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_kill_urbs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_return_all_buffers (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hackrf_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void hackrf_stop_streaming(struct vb2_queue *vq)
{
	struct hackrf_dev *dev = vb2_get_drv_priv(vq);
	struct usb_interface *intf = dev->intf;

	dev_dbg(&intf->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	/* stop hardware streaming */
	hackrf_ctrl_msg(dev, CMD_SET_TRANSCEIVER_MODE, 0, 0, NULL, 0);

	hackrf_kill_urbs(dev);
	hackrf_free_urbs(dev);
	hackrf_free_stream_bufs(dev);

	hackrf_return_all_buffers(vq, VB2_BUF_STATE_ERROR);

	if (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE)
		clear_bit(RX_ON, &dev->flags);
	else
		clear_bit(TX_ON, &dev->flags);

	mutex_unlock(&dev->v4l2_lock);
}
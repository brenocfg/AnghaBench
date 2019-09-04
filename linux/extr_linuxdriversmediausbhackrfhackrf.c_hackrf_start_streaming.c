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
struct hackrf_dev {int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  flags; scalar_t__ sequence; struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_TRANSCEIVER_MODE ; 
 int EBUSY ; 
 int /*<<< orphan*/  RX_ON ; 
 int /*<<< orphan*/  TX_ON ; 
 scalar_t__ V4L2_BUF_TYPE_SDR_CAPTURE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int hackrf_alloc_stream_bufs (struct hackrf_dev*) ; 
 int hackrf_alloc_urbs (struct hackrf_dev*,int) ; 
 int hackrf_ctrl_msg (struct hackrf_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hackrf_free_stream_bufs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_free_urbs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_kill_urbs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  hackrf_return_all_buffers (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int hackrf_set_params (struct hackrf_dev*) ; 
 int hackrf_submit_urbs (struct hackrf_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hackrf_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int hackrf_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct hackrf_dev *dev = vb2_get_drv_priv(vq);
	struct usb_interface *intf = dev->intf;
	int ret;
	unsigned int mode;

	dev_dbg(&intf->dev, "count=%i\n", count);

	mutex_lock(&dev->v4l2_lock);

	/* Allow only RX or TX, not both same time */
	if (vq->type == V4L2_BUF_TYPE_SDR_CAPTURE) {
		if (test_bit(TX_ON, &dev->flags)) {
			ret = -EBUSY;
			goto err_hackrf_return_all_buffers;
		}

		mode = 1;
		set_bit(RX_ON, &dev->flags);
	} else {
		if (test_bit(RX_ON, &dev->flags)) {
			ret = -EBUSY;
			goto err_hackrf_return_all_buffers;
		}

		mode = 2;
		set_bit(TX_ON, &dev->flags);
	}

	dev->sequence = 0;

	ret = hackrf_alloc_stream_bufs(dev);
	if (ret)
		goto err;

	ret = hackrf_alloc_urbs(dev, (mode == 1));
	if (ret)
		goto err;

	ret = hackrf_submit_urbs(dev);
	if (ret)
		goto err;

	ret = hackrf_set_params(dev);
	if (ret)
		goto err;

	/* start hardware streaming */
	ret = hackrf_ctrl_msg(dev, CMD_SET_TRANSCEIVER_MODE, mode, 0, NULL, 0);
	if (ret)
		goto err;

	mutex_unlock(&dev->v4l2_lock);

	return 0;
err:
	hackrf_kill_urbs(dev);
	hackrf_free_urbs(dev);
	hackrf_free_stream_bufs(dev);
	clear_bit(RX_ON, &dev->flags);
	clear_bit(TX_ON, &dev->flags);
err_hackrf_return_all_buffers:
	hackrf_return_all_buffers(vq, VB2_BUF_STATE_QUEUED);
	mutex_unlock(&dev->v4l2_lock);
	dev_dbg(&intf->dev, "failed=%d\n", ret);
	return ret;
}
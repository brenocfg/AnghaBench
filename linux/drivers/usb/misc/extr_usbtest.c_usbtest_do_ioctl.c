#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbtest_param_32 {scalar_t__ iterations; scalar_t__ sglen; int test_num; int length; int /*<<< orphan*/  vary; } ;
struct usbtest_dev {int /*<<< orphan*/  out_pipe; int /*<<< orphan*/  in_pipe; TYPE_3__* int_in; int /*<<< orphan*/  in_int_pipe; TYPE_2__* int_out; int /*<<< orphan*/  out_int_pipe; int /*<<< orphan*/ * iso_in; int /*<<< orphan*/  in_iso_pipe; int /*<<< orphan*/ * iso_out; int /*<<< orphan*/  out_iso_pipe; TYPE_1__* info; } ;
struct usb_sg_request {int dummy; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;
struct scatterlist {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bInterval; } ;
struct TYPE_5__ {int /*<<< orphan*/  bInterval; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_out; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,unsigned int) ; 
 scalar_t__ MAX_SGLEN ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 struct scatterlist* alloc_sglist (scalar_t__,int,int /*<<< orphan*/ ,struct usbtest_dev*,int /*<<< orphan*/ ) ; 
 int ch9_postconfig (struct usbtest_dev*) ; 
 int ctrl_out (struct usbtest_dev*,unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_sglist (struct scatterlist*,scalar_t__) ; 
 int halt_simple (struct usbtest_dev*) ; 
 int /*<<< orphan*/  pattern ; 
 int perform_sglist (struct usbtest_dev*,scalar_t__,int /*<<< orphan*/ ,struct usb_sg_request*,struct scatterlist*,scalar_t__) ; 
 int /*<<< orphan*/  realworld ; 
 struct urb* simple_alloc_urb (struct usb_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_free_urb (struct urb*) ; 
 int simple_io (struct usbtest_dev*,struct urb*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int test_ctrl_queue (struct usbtest_dev*,struct usbtest_param_32*) ; 
 int test_queue (struct usbtest_dev*,struct usbtest_param_32*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int test_unaligned_bulk (struct usbtest_dev*,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,char*) ; 
 struct usb_device* testdev_to_usbdev (struct usbtest_dev*) ; 
 int toggle_sync_simple (struct usbtest_dev*) ; 
 int unlink_queued (struct usbtest_dev*,int /*<<< orphan*/ ,int,int) ; 
 int unlink_simple (struct usbtest_dev*,int /*<<< orphan*/ ,int) ; 
 struct usbtest_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int
usbtest_do_ioctl(struct usb_interface *intf, struct usbtest_param_32 *param)
{
	struct usbtest_dev	*dev = usb_get_intfdata(intf);
	struct usb_device	*udev = testdev_to_usbdev(dev);
	struct urb		*urb;
	struct scatterlist	*sg;
	struct usb_sg_request	req;
	unsigned		i;
	int	retval = -EOPNOTSUPP;

	if (param->iterations <= 0)
		return -EINVAL;
	if (param->sglen > MAX_SGLEN)
		return -EINVAL;
	/*
	 * Just a bunch of test cases that every HCD is expected to handle.
	 *
	 * Some may need specific firmware, though it'd be good to have
	 * one firmware image to handle all the test cases.
	 *
	 * FIXME add more tests!  cancel requests, verify the data, control
	 * queueing, concurrent read+write threads, and so on.
	 */
	switch (param->test_num) {

	case 0:
		dev_info(&intf->dev, "TEST 0:  NOP\n");
		retval = 0;
		break;

	/* Simple non-queued bulk I/O tests */
	case 1:
		if (dev->out_pipe == 0)
			break;
		dev_info(&intf->dev,
				"TEST 1:  write %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_pipe, param->length, 0);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk sink (maybe accepts short writes) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test1");
		simple_free_urb(urb);
		break;
	case 2:
		if (dev->in_pipe == 0)
			break;
		dev_info(&intf->dev,
				"TEST 2:  read %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_pipe, param->length, 0);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk source (maybe generates short writes) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test2");
		simple_free_urb(urb);
		break;
	case 3:
		if (dev->out_pipe == 0 || param->vary == 0)
			break;
		dev_info(&intf->dev,
				"TEST 3:  write/%d 0..%d bytes %u times\n",
				param->vary, param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_pipe, param->length, 0);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk sink (maybe accepts short writes) */
		retval = simple_io(dev, urb, param->iterations, param->vary,
					0, "test3");
		simple_free_urb(urb);
		break;
	case 4:
		if (dev->in_pipe == 0 || param->vary == 0)
			break;
		dev_info(&intf->dev,
				"TEST 4:  read/%d 0..%d bytes %u times\n",
				param->vary, param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_pipe, param->length, 0);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk source (maybe generates short writes) */
		retval = simple_io(dev, urb, param->iterations, param->vary,
					0, "test4");
		simple_free_urb(urb);
		break;

	/* Queued bulk I/O tests */
	case 5:
		if (dev->out_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 5:  write %d sglists %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				0, dev, dev->out_pipe);
		if (!sg) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk sink (maybe accepts short writes) */
		retval = perform_sglist(dev, param->iterations, dev->out_pipe,
				&req, sg, param->sglen);
		free_sglist(sg, param->sglen);
		break;

	case 6:
		if (dev->in_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 6:  read %d sglists %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				0, dev, dev->in_pipe);
		if (!sg) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk source (maybe generates short writes) */
		retval = perform_sglist(dev, param->iterations, dev->in_pipe,
				&req, sg, param->sglen);
		free_sglist(sg, param->sglen);
		break;
	case 7:
		if (dev->out_pipe == 0 || param->sglen == 0 || param->vary == 0)
			break;
		dev_info(&intf->dev,
			"TEST 7:  write/%d %d sglists %d entries 0..%d bytes\n",
				param->vary, param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				param->vary, dev, dev->out_pipe);
		if (!sg) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk sink (maybe accepts short writes) */
		retval = perform_sglist(dev, param->iterations, dev->out_pipe,
				&req, sg, param->sglen);
		free_sglist(sg, param->sglen);
		break;
	case 8:
		if (dev->in_pipe == 0 || param->sglen == 0 || param->vary == 0)
			break;
		dev_info(&intf->dev,
			"TEST 8:  read/%d %d sglists %d entries 0..%d bytes\n",
				param->vary, param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				param->vary, dev, dev->in_pipe);
		if (!sg) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE:  bulk source (maybe generates short writes) */
		retval = perform_sglist(dev, param->iterations, dev->in_pipe,
				&req, sg, param->sglen);
		free_sglist(sg, param->sglen);
		break;

	/* non-queued sanity tests for control (chapter 9 subset) */
	case 9:
		retval = 0;
		dev_info(&intf->dev,
			"TEST 9:  ch9 (subset) control tests, %d times\n",
				param->iterations);
		for (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = ch9_postconfig(dev);
		if (retval)
			dev_err(&intf->dev, "ch9 subset failed, "
					"iterations left %d\n", i);
		break;

	/* queued control messaging */
	case 10:
		retval = 0;
		dev_info(&intf->dev,
				"TEST 10:  queue %d control calls, %d times\n",
				param->sglen,
				param->iterations);
		retval = test_ctrl_queue(dev, param);
		break;

	/* simple non-queued unlinks (ring with one urb) */
	case 11:
		if (dev->in_pipe == 0 || !param->length)
			break;
		retval = 0;
		dev_info(&intf->dev, "TEST 11:  unlink %d reads of %d\n",
				param->iterations, param->length);
		for (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = unlink_simple(dev, dev->in_pipe,
						param->length);
		if (retval)
			dev_err(&intf->dev, "unlink reads failed %d, "
				"iterations left %d\n", retval, i);
		break;
	case 12:
		if (dev->out_pipe == 0 || !param->length)
			break;
		retval = 0;
		dev_info(&intf->dev, "TEST 12:  unlink %d writes of %d\n",
				param->iterations, param->length);
		for (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = unlink_simple(dev, dev->out_pipe,
						param->length);
		if (retval)
			dev_err(&intf->dev, "unlink writes failed %d, "
				"iterations left %d\n", retval, i);
		break;

	/* ep halt tests */
	case 13:
		if (dev->out_pipe == 0 && dev->in_pipe == 0)
			break;
		retval = 0;
		dev_info(&intf->dev, "TEST 13:  set/clear %d halts\n",
				param->iterations);
		for (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = halt_simple(dev);

		if (retval)
			ERROR(dev, "halts failed, iterations left %d\n", i);
		break;

	/* control write tests */
	case 14:
		if (!dev->info->ctrl_out)
			break;
		dev_info(&intf->dev, "TEST 14:  %d ep0out, %d..%d vary %d\n",
				param->iterations,
				realworld ? 1 : 0, param->length,
				param->vary);
		retval = ctrl_out(dev, param->iterations,
				param->length, param->vary, 0);
		break;

	/* iso write tests */
	case 15:
		if (dev->out_iso_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 15:  write %d iso, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		/* FIRMWARE:  iso sink */
		retval = test_queue(dev, param,
				dev->out_iso_pipe, dev->iso_out, 0);
		break;

	/* iso read tests */
	case 16:
		if (dev->in_iso_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 16:  read %d iso, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		/* FIRMWARE:  iso source */
		retval = test_queue(dev, param,
				dev->in_iso_pipe, dev->iso_in, 0);
		break;

	/* FIXME scatterlist cancel (needs helper thread) */

	/* Tests for bulk I/O using DMA mapping by core and odd address */
	case 17:
		if (dev->out_pipe == 0)
			break;
		dev_info(&intf->dev,
			"TEST 17:  write odd addr %d bytes %u times core map\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->out_pipe,
				param->length, param->iterations,
				0, "test17");
		break;

	case 18:
		if (dev->in_pipe == 0)
			break;
		dev_info(&intf->dev,
			"TEST 18:  read odd addr %d bytes %u times core map\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->in_pipe,
				param->length, param->iterations,
				0, "test18");
		break;

	/* Tests for bulk I/O using premapped coherent buffer and odd address */
	case 19:
		if (dev->out_pipe == 0)
			break;
		dev_info(&intf->dev,
			"TEST 19:  write odd addr %d bytes %u times premapped\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->out_pipe,
				param->length, param->iterations,
				URB_NO_TRANSFER_DMA_MAP, "test19");
		break;

	case 20:
		if (dev->in_pipe == 0)
			break;
		dev_info(&intf->dev,
			"TEST 20:  read odd addr %d bytes %u times premapped\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->in_pipe,
				param->length, param->iterations,
				URB_NO_TRANSFER_DMA_MAP, "test20");
		break;

	/* control write tests with unaligned buffer */
	case 21:
		if (!dev->info->ctrl_out)
			break;
		dev_info(&intf->dev,
				"TEST 21:  %d ep0out odd addr, %d..%d vary %d\n",
				param->iterations,
				realworld ? 1 : 0, param->length,
				param->vary);
		retval = ctrl_out(dev, param->iterations,
				param->length, param->vary, 1);
		break;

	/* unaligned iso tests */
	case 22:
		if (dev->out_iso_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 22:  write %d iso odd, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		retval = test_queue(dev, param,
				dev->out_iso_pipe, dev->iso_out, 1);
		break;

	case 23:
		if (dev->in_iso_pipe == 0 || param->sglen == 0)
			break;
		dev_info(&intf->dev,
			"TEST 23:  read %d iso odd, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		retval = test_queue(dev, param,
				dev->in_iso_pipe, dev->iso_in, 1);
		break;

	/* unlink URBs from a bulk-OUT queue */
	case 24:
		if (dev->out_pipe == 0 || !param->length || param->sglen < 4)
			break;
		retval = 0;
		dev_info(&intf->dev, "TEST 24:  unlink from %d queues of "
				"%d %d-byte writes\n",
				param->iterations, param->sglen, param->length);
		for (i = param->iterations; retval == 0 && i > 0; --i) {
			retval = unlink_queued(dev, dev->out_pipe,
						param->sglen, param->length);
			if (retval) {
				dev_err(&intf->dev,
					"unlink queued writes failed %d, "
					"iterations left %d\n", retval, i);
				break;
			}
		}
		break;

	/* Simple non-queued interrupt I/O tests */
	case 25:
		if (dev->out_int_pipe == 0)
			break;
		dev_info(&intf->dev,
				"TEST 25: write %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_int_pipe, param->length,
				dev->int_out->bInterval);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE: interrupt sink (maybe accepts short writes) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test25");
		simple_free_urb(urb);
		break;
	case 26:
		if (dev->in_int_pipe == 0)
			break;
		dev_info(&intf->dev,
				"TEST 26: read %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_int_pipe, param->length,
				dev->int_in->bInterval);
		if (!urb) {
			retval = -ENOMEM;
			break;
		}
		/* FIRMWARE: interrupt source (maybe generates short writes) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test26");
		simple_free_urb(urb);
		break;
	case 27:
		/* We do performance test, so ignore data compare */
		if (dev->out_pipe == 0 || param->sglen == 0 || pattern != 0)
			break;
		dev_info(&intf->dev,
			"TEST 27: bulk write %dMbytes\n", (param->iterations *
			param->sglen * param->length) / (1024 * 1024));
		retval = test_queue(dev, param,
				dev->out_pipe, NULL, 0);
		break;
	case 28:
		if (dev->in_pipe == 0 || param->sglen == 0 || pattern != 0)
			break;
		dev_info(&intf->dev,
			"TEST 28: bulk read %dMbytes\n", (param->iterations *
			param->sglen * param->length) / (1024 * 1024));
		retval = test_queue(dev, param,
				dev->in_pipe, NULL, 0);
		break;
	/* Test data Toggle/seq_nr clear between bulk out transfers */
	case 29:
		if (dev->out_pipe == 0)
			break;
		retval = 0;
		dev_info(&intf->dev, "TEST 29: Clear toggle between bulk writes %d times\n",
				param->iterations);
		for (i = param->iterations; retval == 0 && i > 0; --i)
			retval = toggle_sync_simple(dev);

		if (retval)
			ERROR(dev, "toggle sync failed, iterations left %d\n",
			      i);
		break;
	}
	return retval;
}
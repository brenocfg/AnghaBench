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
struct xenkbd_info {int irq; int gref; int mtouch_cur_contact_id; struct input_dev* mtouch; struct xenbus_device* xbdev; int /*<<< orphan*/  phys; struct input_dev* ptr; struct input_dev* kbd; void* page; } ;
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {char* nodename; int /*<<< orphan*/  otherend; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int vendor; int product; void* bustype; } ;
struct input_dev {char* name; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BTN_LEFT ; 
 int BTN_TASK ; 
 void* BUS_PCI ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EV_ABS ; 
 int EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int KEY_ESC ; 
 int KEY_MAX ; 
 int KEY_OK ; 
 int KEY_UNKNOWN ; 
 size_t KPARAM_X ; 
 size_t KPARAM_Y ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int XENFB_HEIGHT ; 
 int XENFB_WIDTH ; 
 int /*<<< orphan*/  XENKBD_FIELD_FEAT_ABS_POINTER ; 
 int /*<<< orphan*/  XENKBD_FIELD_FEAT_DSBL_KEYBRD ; 
 int /*<<< orphan*/  XENKBD_FIELD_FEAT_DSBL_POINTER ; 
 int /*<<< orphan*/  XENKBD_FIELD_FEAT_MTOUCH ; 
 int /*<<< orphan*/  XENKBD_FIELD_HEIGHT ; 
 int /*<<< orphan*/  XENKBD_FIELD_MT_HEIGHT ; 
 int /*<<< orphan*/  XENKBD_FIELD_MT_NUM_CONTACTS ; 
 int /*<<< orphan*/  XENKBD_FIELD_MT_WIDTH ; 
 int /*<<< orphan*/  XENKBD_FIELD_REQ_ABS_POINTER ; 
 int /*<<< orphan*/  XENKBD_FIELD_REQ_MTOUCH ; 
 int /*<<< orphan*/  XENKBD_FIELD_WIDTH ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct xenkbd_info*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_mt_init_slots (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xenkbd_info* kzalloc (int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* ptr_size ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 void* xenbus_read_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xenbus_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int xenkbd_connect_backend (struct xenbus_device*,struct xenkbd_info*) ; 
 int /*<<< orphan*/  xenkbd_remove (struct xenbus_device*) ; 

__attribute__((used)) static int xenkbd_probe(struct xenbus_device *dev,
				  const struct xenbus_device_id *id)
{
	int ret, i;
	bool with_mtouch, with_kbd, with_ptr;
	struct xenkbd_info *info;
	struct input_dev *kbd, *ptr, *mtouch;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating info structure");
		return -ENOMEM;
	}
	dev_set_drvdata(&dev->dev, info);
	info->xbdev = dev;
	info->irq = -1;
	info->gref = -1;
	snprintf(info->phys, sizeof(info->phys), "xenbus/%s", dev->nodename);

	info->page = (void *)__get_free_page(GFP_KERNEL | __GFP_ZERO);
	if (!info->page)
		goto error_nomem;

	/*
	 * The below are reverse logic, e.g. if the feature is set, then
	 * do not expose the corresponding virtual device.
	 */
	with_kbd = !xenbus_read_unsigned(dev->otherend,
					 XENKBD_FIELD_FEAT_DSBL_KEYBRD, 0);

	with_ptr = !xenbus_read_unsigned(dev->otherend,
					 XENKBD_FIELD_FEAT_DSBL_POINTER, 0);

	/* Direct logic: if set, then create multi-touch device. */
	with_mtouch = xenbus_read_unsigned(dev->otherend,
					   XENKBD_FIELD_FEAT_MTOUCH, 0);
	if (with_mtouch) {
		ret = xenbus_write(XBT_NIL, dev->nodename,
				   XENKBD_FIELD_REQ_MTOUCH, "1");
		if (ret) {
			pr_warn("xenkbd: can't request multi-touch");
			with_mtouch = 0;
		}
	}

	/* keyboard */
	if (with_kbd) {
		kbd = input_allocate_device();
		if (!kbd)
			goto error_nomem;
		kbd->name = "Xen Virtual Keyboard";
		kbd->phys = info->phys;
		kbd->id.bustype = BUS_PCI;
		kbd->id.vendor = 0x5853;
		kbd->id.product = 0xffff;

		__set_bit(EV_KEY, kbd->evbit);
		for (i = KEY_ESC; i < KEY_UNKNOWN; i++)
			__set_bit(i, kbd->keybit);
		for (i = KEY_OK; i < KEY_MAX; i++)
			__set_bit(i, kbd->keybit);

		ret = input_register_device(kbd);
		if (ret) {
			input_free_device(kbd);
			xenbus_dev_fatal(dev, ret,
					 "input_register_device(kbd)");
			goto error;
		}
		info->kbd = kbd;
	}

	/* pointing device */
	if (with_ptr) {
		unsigned int abs;

		/* Set input abs params to match backend screen res */
		abs = xenbus_read_unsigned(dev->otherend,
					   XENKBD_FIELD_FEAT_ABS_POINTER, 0);
		ptr_size[KPARAM_X] = xenbus_read_unsigned(dev->otherend,
							  XENKBD_FIELD_WIDTH,
							  ptr_size[KPARAM_X]);
		ptr_size[KPARAM_Y] = xenbus_read_unsigned(dev->otherend,
							  XENKBD_FIELD_HEIGHT,
							  ptr_size[KPARAM_Y]);
		if (abs) {
			ret = xenbus_write(XBT_NIL, dev->nodename,
					   XENKBD_FIELD_REQ_ABS_POINTER, "1");
			if (ret) {
				pr_warn("xenkbd: can't request abs-pointer\n");
				abs = 0;
			}
		}

		ptr = input_allocate_device();
		if (!ptr)
			goto error_nomem;
		ptr->name = "Xen Virtual Pointer";
		ptr->phys = info->phys;
		ptr->id.bustype = BUS_PCI;
		ptr->id.vendor = 0x5853;
		ptr->id.product = 0xfffe;

		if (abs) {
			__set_bit(EV_ABS, ptr->evbit);
			input_set_abs_params(ptr, ABS_X, 0,
					     ptr_size[KPARAM_X], 0, 0);
			input_set_abs_params(ptr, ABS_Y, 0,
					     ptr_size[KPARAM_Y], 0, 0);
		} else {
			input_set_capability(ptr, EV_REL, REL_X);
			input_set_capability(ptr, EV_REL, REL_Y);
		}
		input_set_capability(ptr, EV_REL, REL_WHEEL);

		__set_bit(EV_KEY, ptr->evbit);
		for (i = BTN_LEFT; i <= BTN_TASK; i++)
			__set_bit(i, ptr->keybit);

		ret = input_register_device(ptr);
		if (ret) {
			input_free_device(ptr);
			xenbus_dev_fatal(dev, ret,
					 "input_register_device(ptr)");
			goto error;
		}
		info->ptr = ptr;
	}

	/* multi-touch device */
	if (with_mtouch) {
		int num_cont, width, height;

		mtouch = input_allocate_device();
		if (!mtouch)
			goto error_nomem;

		num_cont = xenbus_read_unsigned(info->xbdev->otherend,
						XENKBD_FIELD_MT_NUM_CONTACTS,
						1);
		width = xenbus_read_unsigned(info->xbdev->otherend,
					     XENKBD_FIELD_MT_WIDTH,
					     XENFB_WIDTH);
		height = xenbus_read_unsigned(info->xbdev->otherend,
					      XENKBD_FIELD_MT_HEIGHT,
					      XENFB_HEIGHT);

		mtouch->name = "Xen Virtual Multi-touch";
		mtouch->phys = info->phys;
		mtouch->id.bustype = BUS_PCI;
		mtouch->id.vendor = 0x5853;
		mtouch->id.product = 0xfffd;

		input_set_abs_params(mtouch, ABS_MT_TOUCH_MAJOR,
				     0, 255, 0, 0);
		input_set_abs_params(mtouch, ABS_MT_POSITION_X,
				     0, width, 0, 0);
		input_set_abs_params(mtouch, ABS_MT_POSITION_Y,
				     0, height, 0, 0);

		ret = input_mt_init_slots(mtouch, num_cont, INPUT_MT_DIRECT);
		if (ret) {
			input_free_device(mtouch);
			xenbus_dev_fatal(info->xbdev, ret,
					 "input_mt_init_slots");
			goto error;
		}

		ret = input_register_device(mtouch);
		if (ret) {
			input_free_device(mtouch);
			xenbus_dev_fatal(info->xbdev, ret,
					 "input_register_device(mtouch)");
			goto error;
		}
		info->mtouch_cur_contact_id = -1;
		info->mtouch = mtouch;
	}

	if (!(with_kbd || with_ptr || with_mtouch)) {
		ret = -ENXIO;
		goto error;
	}

	ret = xenkbd_connect_backend(dev, info);
	if (ret < 0)
		goto error;

	return 0;

 error_nomem:
	ret = -ENOMEM;
	xenbus_dev_fatal(dev, ret, "allocating device memory");
 error:
	xenkbd_remove(dev);
	return ret;
}
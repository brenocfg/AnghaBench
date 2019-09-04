#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ushc_data {int caps; TYPE_1__* usb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USHC_GET_CAPS ; 
 int /*<<< orphan*/  USHC_GET_CAPS_TYPE ; 
 int USHC_GET_CAPS_VERSION_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int le32_to_cpu (int) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ushc_hw_get_caps(struct ushc_data *ushc)
{
	int ret;
	int version;

	ret = usb_control_msg(ushc->usb_dev, usb_rcvctrlpipe(ushc->usb_dev, 0),
			      USHC_GET_CAPS, USHC_GET_CAPS_TYPE,
			      0, 0, &ushc->caps, sizeof(ushc->caps), 100);
	if (ret < 0)
		return ret;

	ushc->caps = le32_to_cpu(ushc->caps);

	version = ushc->caps & USHC_GET_CAPS_VERSION_MASK;
	if (version != 0x02) {
		dev_err(&ushc->usb_dev->dev, "controller version %d is not supported\n", version);
		return -EINVAL;
	}

	return 0;
}
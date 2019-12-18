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
struct TYPE_2__ {int exttype; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int __u8 ;

/* Variables and functions */
#define  WIIMOTE_EXT_BALANCE_BOARD 135 
#define  WIIMOTE_EXT_CLASSIC_CONTROLLER 134 
#define  WIIMOTE_EXT_DRUMS 133 
#define  WIIMOTE_EXT_GUITAR 132 
#define  WIIMOTE_EXT_NONE 131 
#define  WIIMOTE_EXT_NUNCHUK 130 
#define  WIIMOTE_EXT_PRO_CONTROLLER 129 
#define  WIIMOTE_EXT_UNKNOWN 128 
 struct wiimote_data* dev_to_wii (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t wiimote_ext_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	unsigned long flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	type = wdata->state.exttype;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	switch (type) {
	case WIIMOTE_EXT_NONE:
		return sprintf(buf, "none\n");
	case WIIMOTE_EXT_NUNCHUK:
		return sprintf(buf, "nunchuk\n");
	case WIIMOTE_EXT_CLASSIC_CONTROLLER:
		return sprintf(buf, "classic\n");
	case WIIMOTE_EXT_BALANCE_BOARD:
		return sprintf(buf, "balanceboard\n");
	case WIIMOTE_EXT_PRO_CONTROLLER:
		return sprintf(buf, "procontroller\n");
	case WIIMOTE_EXT_DRUMS:
		return sprintf(buf, "drums\n");
	case WIIMOTE_EXT_GUITAR:
		return sprintf(buf, "guitar\n");
	case WIIMOTE_EXT_UNKNOWN:
		/* fallthrough */
	default:
		return sprintf(buf, "unknown\n");
	}
}
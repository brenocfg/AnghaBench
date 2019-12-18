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
struct TYPE_2__ {int devtype; int /*<<< orphan*/  lock; } ;
struct wiimote_data {TYPE_1__ state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int __u8 ;

/* Variables and functions */
#define  WIIMOTE_DEV_BALANCE_BOARD 134 
#define  WIIMOTE_DEV_GEN10 133 
#define  WIIMOTE_DEV_GEN20 132 
#define  WIIMOTE_DEV_GENERIC 131 
#define  WIIMOTE_DEV_PENDING 130 
#define  WIIMOTE_DEV_PRO_CONTROLLER 129 
#define  WIIMOTE_DEV_UNKNOWN 128 
 struct wiimote_data* dev_to_wii (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t wiimote_dev_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	unsigned long flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	type = wdata->state.devtype;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	switch (type) {
	case WIIMOTE_DEV_GENERIC:
		return sprintf(buf, "generic\n");
	case WIIMOTE_DEV_GEN10:
		return sprintf(buf, "gen10\n");
	case WIIMOTE_DEV_GEN20:
		return sprintf(buf, "gen20\n");
	case WIIMOTE_DEV_BALANCE_BOARD:
		return sprintf(buf, "balanceboard\n");
	case WIIMOTE_DEV_PRO_CONTROLLER:
		return sprintf(buf, "procontroller\n");
	case WIIMOTE_DEV_PENDING:
		return sprintf(buf, "pending\n");
	case WIIMOTE_DEV_UNKNOWN:
		/* fallthrough */
	default:
		return sprintf(buf, "unknown\n");
	}
}
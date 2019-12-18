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
typedef  int /*<<< orphan*/  u32 ;
struct redrat3_dev {int /*<<< orphan*/  carrier; struct device* dev; } ;
struct rc_dev {struct redrat3_dev* priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redrat3_set_tx_carrier(struct rc_dev *rcdev, u32 carrier)
{
	struct redrat3_dev *rr3 = rcdev->priv;
	struct device *dev = rr3->dev;

	dev_dbg(dev, "Setting modulation frequency to %u", carrier);
	if (carrier == 0)
		return -EINVAL;

	rr3->carrier = carrier;

	return 0;
}
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
struct em28xx {int devno; struct em28xx* dev_next; int /*<<< orphan*/  name; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EM28XX_MAXBOARDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  em28xx_devused ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct em28xx*) ; 
 struct em28xx* kmemdup (struct em28xx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_duplicate_dev(struct em28xx *dev)
{
	int nr;
	struct em28xx *sec_dev = kmemdup(dev, sizeof(*sec_dev), GFP_KERNEL);

	if (!sec_dev) {
		dev->dev_next = NULL;
		return -ENOMEM;
	}
	/* Check to see next free device and mark as used */
	do {
		nr = find_first_zero_bit(em28xx_devused, EM28XX_MAXBOARDS);
		if (nr >= EM28XX_MAXBOARDS) {
			/* No free device slots */
			dev_warn(&dev->intf->dev, ": Supports only %i em28xx boards.\n",
				 EM28XX_MAXBOARDS);
			kfree(sec_dev);
			dev->dev_next = NULL;
			return -ENOMEM;
		}
	} while (test_and_set_bit(nr, em28xx_devused));
	sec_dev->devno = nr;
	snprintf(sec_dev->name, 28, "em28xx #%d", nr);
	sec_dev->dev_next = NULL;
	dev->dev_next = sec_dev;
	return 0;
}
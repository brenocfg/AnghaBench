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
struct TYPE_2__ {scalar_t__ parent; } ;
struct input_dev {TYPE_1__ dev; int /*<<< orphan*/  poller; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 

__attribute__((used)) static bool input_dev_ensure_poller(struct input_dev *dev)
{
	if (!dev->poller) {
		dev_err(dev->dev.parent ?: &dev->dev,
			"poller structure has not been set up\n");
		return false;
	}

	return true;
}
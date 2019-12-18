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
struct slim_eaddr {int dummy; } ;
struct slim_device {int dummy; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* device_find_child (int /*<<< orphan*/ ,struct slim_eaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_match_dev ; 
 struct slim_device* to_slim_device (struct device*) ; 

__attribute__((used)) static struct slim_device *find_slim_device(struct slim_controller *ctrl,
					    struct slim_eaddr *eaddr)
{
	struct slim_device *sbdev;
	struct device *dev;

	dev = device_find_child(ctrl->dev, eaddr, slim_match_dev);
	if (dev) {
		sbdev = to_slim_device(dev);
		return sbdev;
	}

	return NULL;
}
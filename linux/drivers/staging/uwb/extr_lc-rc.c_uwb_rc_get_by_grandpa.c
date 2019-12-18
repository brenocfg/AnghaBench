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
struct uwb_rc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device const*,int /*<<< orphan*/ ) ; 
 struct uwb_rc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  find_rc_grandpa ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  uwb_rc_class ; 

struct uwb_rc *uwb_rc_get_by_grandpa(const struct device *grandpa_dev)
{
	struct device *dev;
	struct uwb_rc *rc = NULL;

	dev = class_find_device(&uwb_rc_class, NULL, grandpa_dev,
				find_rc_grandpa);
	if (dev) {
		rc = dev_get_drvdata(dev);
		put_device(dev);
	}

	return rc;
}
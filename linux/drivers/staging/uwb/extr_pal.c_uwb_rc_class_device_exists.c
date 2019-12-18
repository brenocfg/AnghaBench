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
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct uwb_rc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_rc ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  uwb_rc_class ; 

__attribute__((used)) static bool uwb_rc_class_device_exists(struct uwb_rc *target_rc)
{
	struct device *dev;

	dev = class_find_device(&uwb_rc_class, NULL, target_rc,	find_rc);

	put_device(dev);

	return (dev != NULL);
}
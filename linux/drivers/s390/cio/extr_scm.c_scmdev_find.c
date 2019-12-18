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
struct scm_device {int dummy; } ;
struct sale {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sale*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_address ; 
 int /*<<< orphan*/  scm_bus_type ; 
 struct scm_device* to_scm_dev (struct device*) ; 

__attribute__((used)) static struct scm_device *scmdev_find(struct sale *sale)
{
	struct device *dev;

	dev = bus_find_device(&scm_bus_type, NULL, sale, check_address);

	return dev ? to_scm_dev(dev) : NULL;
}
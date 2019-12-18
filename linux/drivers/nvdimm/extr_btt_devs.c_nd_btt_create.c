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
struct nd_region {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* __nd_btt_create (struct nd_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __nd_device_register (struct device*) ; 

struct device *nd_btt_create(struct nd_region *nd_region)
{
	struct device *dev = __nd_btt_create(nd_region, 0, NULL, NULL);

	__nd_device_register(dev);
	return dev;
}
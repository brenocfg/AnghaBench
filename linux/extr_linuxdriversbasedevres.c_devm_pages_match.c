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
struct pages_devres {scalar_t__ addr; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int devm_pages_match(struct device *dev, void *res, void *p)
{
	struct pages_devres *devres = res;
	struct pages_devres *target = p;

	return devres->addr == target->addr;
}
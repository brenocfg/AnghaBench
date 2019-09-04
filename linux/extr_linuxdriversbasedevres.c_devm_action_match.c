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
struct device {int dummy; } ;
struct action_devres {scalar_t__ action; scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static int devm_action_match(struct device *dev, void *res, void *p)
{
	struct action_devres *devres = res;
	struct action_devres *target = p;

	return devres->action == target->action &&
	       devres->data == target->data;
}
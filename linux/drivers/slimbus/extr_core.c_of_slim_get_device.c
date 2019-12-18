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
struct slim_device {int dummy; } ;
struct slim_controller {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct slim_device* of_find_slim_device (struct slim_controller*,struct device_node*) ; 

struct slim_device *of_slim_get_device(struct slim_controller *ctrl,
				       struct device_node *np)
{
	return of_find_slim_device(ctrl, np);
}
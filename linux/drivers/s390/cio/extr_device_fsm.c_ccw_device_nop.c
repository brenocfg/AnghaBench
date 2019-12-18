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
struct ccw_device {int dummy; } ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;

/* Variables and functions */

__attribute__((used)) static void
ccw_device_nop(struct ccw_device *cdev, enum dev_event dev_event)
{
}
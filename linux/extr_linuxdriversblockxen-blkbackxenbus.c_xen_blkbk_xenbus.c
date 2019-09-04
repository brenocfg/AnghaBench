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
struct xenbus_device {int dummy; } ;
struct backend_info {struct xenbus_device* dev; } ;

/* Variables and functions */

struct xenbus_device *xen_blkbk_xenbus(struct backend_info *be)
{
	return be->dev;
}
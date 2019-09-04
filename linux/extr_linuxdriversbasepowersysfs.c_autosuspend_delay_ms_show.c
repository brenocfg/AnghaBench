#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct TYPE_2__ {int autosuspend_delay; int /*<<< orphan*/  use_autosuspend; } ;
struct device {TYPE_1__ power; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t autosuspend_delay_ms_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	if (!dev->power.use_autosuspend)
		return -EIO;
	return sprintf(buf, "%d\n", dev->power.autosuspend_delay);
}
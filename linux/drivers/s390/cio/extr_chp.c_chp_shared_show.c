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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct channel_path {int shared; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct channel_path* to_channelpath (struct device*) ; 

__attribute__((used)) static ssize_t chp_shared_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct channel_path *chp = to_channelpath(dev);

	if (!chp)
		return 0;
	if (chp->shared == -1) /* channel measurements not available */
		return sprintf(buf, "unknown\n");
	return sprintf(buf, "%x\n", chp->shared);
}
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
struct most_channel {int is_starving; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct most_channel* to_channel (struct device*) ; 

__attribute__((used)) static ssize_t channel_starving_show(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct most_channel *c = to_channel(dev);

	return snprintf(buf, PAGE_SIZE, "%d\n", c->is_starving);
}
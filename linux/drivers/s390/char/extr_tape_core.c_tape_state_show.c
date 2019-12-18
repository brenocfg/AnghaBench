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
struct tape_device {scalar_t__ first_minor; size_t tape_state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct tape_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 char** tape_state_verbose ; 

__attribute__((used)) static ssize_t
tape_state_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct tape_device *tdev;

	tdev = dev_get_drvdata(dev);
	return scnprintf(buf, PAGE_SIZE, "%s\n", (tdev->first_minor < 0) ?
		"OFFLINE" : tape_state_verbose[tdev->tape_state]);
}
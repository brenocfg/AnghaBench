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
struct rio_dev {scalar_t__ prev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* rio_name (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct rio_dev* to_rio_dev (struct device*) ; 

__attribute__((used)) static ssize_t lprev_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct rio_dev *rdev = to_rio_dev(dev);

	return sprintf(buf, "%s\n",
			(rdev->prev) ? rio_name(rdev->prev) : "root");
}
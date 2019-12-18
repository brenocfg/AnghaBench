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
struct gb_control {int /*<<< orphan*/  product_string; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct gb_control* to_gb_control (struct device*) ; 

__attribute__((used)) static ssize_t product_string_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct gb_control *control = to_gb_control(dev);

	return scnprintf(buf, PAGE_SIZE, "%s\n", control->product_string);
}
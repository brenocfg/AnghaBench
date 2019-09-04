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
struct eisa_device {int state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int EISA_CONFIG_ENABLED ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct eisa_device* to_eisa_device (struct device*) ; 

__attribute__((used)) static ssize_t eisa_show_state(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct eisa_device *edev = to_eisa_device(dev);
	return sprintf(buf, "%d\n", edev->state & EISA_CONFIG_ENABLED);
}
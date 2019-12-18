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
struct fieldbus_dev {int fieldbus_type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  FIELDBUS_DEV_TYPE_PROFINET 128 
 struct fieldbus_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t fieldbus_type_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct fieldbus_dev *fb = dev_get_drvdata(dev);
	const char *t;

	switch (fb->fieldbus_type) {
	case FIELDBUS_DEV_TYPE_PROFINET:
		t = "profinet";
		break;
	default:
		t = "unknown";
		break;
	}

	return sprintf(buf, "%s\n", t);
}
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
struct fieldbus_dev {int /*<<< orphan*/  (* fieldbus_id_get ) (struct fieldbus_dev*,char*,int /*<<< orphan*/ ) ;} ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fieldbus_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct fieldbus_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fieldbus_id_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct fieldbus_dev *fb = dev_get_drvdata(dev);

	return fb->fieldbus_id_get(fb, buf, PAGE_SIZE);
}
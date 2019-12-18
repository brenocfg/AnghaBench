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
struct TYPE_2__ {int quirks; } ;
struct mt_device {TYPE_1__ mtclass; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct mt_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t mt_show_quirks(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct mt_device *td = hid_get_drvdata(hdev);

	return sprintf(buf, "%u\n", td->mtclass.quirks);
}
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
struct ntrig_data {int sensor_logical_height; } ;
struct hid_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct ntrig_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static ssize_t show_log_height(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct hid_device *hdev = to_hid_device(dev);
	struct ntrig_data *nd = hid_get_drvdata(hdev);

	return sprintf(buf, "%d\n", nd->sensor_logical_height);
}
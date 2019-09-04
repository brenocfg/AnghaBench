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
struct hv_device {int /*<<< orphan*/  channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * monitor_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int channel_conn_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hv_device* device_to_hv_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__ vmbus_connection ; 

__attribute__((used)) static ssize_t client_monitor_conn_id_show(struct device *dev,
					   struct device_attribute *dev_attr,
					   char *buf)
{
	struct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channel)
		return -ENODEV;
	return sprintf(buf, "%d\n",
		       channel_conn_id(hv_dev->channel,
				       vmbus_connection.monitor_pages[1]));
}
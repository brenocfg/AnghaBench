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
struct hv_ring_buffer_debug_info {int current_read_index; } ;
struct hv_device {TYPE_1__* channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  inbound; } ;

/* Variables and functions */
 int ENODEV ; 
 struct hv_device* device_to_hv_device (struct device*) ; 
 int hv_ringbuffer_get_debuginfo (int /*<<< orphan*/ *,struct hv_ring_buffer_debug_info*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t in_read_index_show(struct device *dev,
				  struct device_attribute *dev_attr, char *buf)
{
	struct hv_device *hv_dev = device_to_hv_device(dev);
	struct hv_ring_buffer_debug_info inbound;
	int ret;

	if (!hv_dev->channel)
		return -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", inbound.current_read_index);
}
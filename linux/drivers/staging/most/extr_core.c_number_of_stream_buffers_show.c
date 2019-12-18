#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct most_channel {unsigned int channel_id; TYPE_2__* iface; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* channel_vector; } ;
struct TYPE_3__ {int num_buffers_streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct most_channel* to_channel (struct device*) ; 

__attribute__((used)) static ssize_t number_of_stream_buffers_show(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct most_channel *c = to_channel(dev);
	unsigned int i = c->channel_id;

	return snprintf(buf, PAGE_SIZE, "%d\n",
			c->iface->channel_vector[i].num_buffers_streaming);
}
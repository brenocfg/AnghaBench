#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hv_device {TYPE_4__* channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  b; } ;
struct TYPE_6__ {TYPE_1__ if_type; } ;
struct TYPE_7__ {TYPE_2__ offer; } ;
struct TYPE_8__ {TYPE_3__ offermsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct hv_device* device_to_hv_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t class_id_show(struct device *dev,
			       struct device_attribute *dev_attr, char *buf)
{
	struct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channel)
		return -ENODEV;
	return sprintf(buf, "{%pUl}\n",
		       hv_dev->channel->offermsg.offer.if_type.b);
}
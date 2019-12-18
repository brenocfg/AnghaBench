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
struct device {int dummy; } ;
struct TYPE_2__ {int qid; } ;

/* Variables and functions */
 scalar_t__ is_queue_dev (struct device*) ; 
 TYPE_1__* to_ap_queue (struct device*) ; 

__attribute__((used)) static int __match_queue_device_with_qid(struct device *dev, const void *data)
{
	return is_queue_dev(dev) && to_ap_queue(dev)->qid == (int)(long) data;
}
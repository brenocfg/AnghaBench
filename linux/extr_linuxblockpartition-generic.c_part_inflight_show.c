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
struct request_queue {int dummy; } ;
struct hd_struct {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 struct hd_struct* dev_to_part (struct device*) ; 
 int /*<<< orphan*/  part_in_flight_rw (struct request_queue*,struct hd_struct*,unsigned int*) ; 
 TYPE_1__* part_to_disk (struct hd_struct*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,unsigned int) ; 

ssize_t part_inflight_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct hd_struct *p = dev_to_part(dev);
	struct request_queue *q = part_to_disk(p)->queue;
	unsigned int inflight[2];

	part_in_flight_rw(q, p, inflight);
	return sprintf(buf, "%8u %8u\n", inflight[0], inflight[1]);
}
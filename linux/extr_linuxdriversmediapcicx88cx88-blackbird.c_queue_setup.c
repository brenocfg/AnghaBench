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
struct vb2_queue {struct cx8802_dev* drv_priv; } ;
struct device {int dummy; } ;
struct cx8802_dev {int ts_packet_size; int ts_packet_count; } ;

/* Variables and functions */

__attribute__((used)) static int queue_setup(struct vb2_queue *q,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct cx8802_dev *dev = q->drv_priv;

	*num_planes = 1;
	dev->ts_packet_size  = 188 * 4;
	dev->ts_packet_count  = 32;
	sizes[0] = dev->ts_packet_size * dev->ts_packet_count;
	return 0;
}
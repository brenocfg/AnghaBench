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
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int GO7007_BUF_SIZE ; 

__attribute__((used)) static int go7007_queue_setup(struct vb2_queue *q,
		unsigned int *num_buffers, unsigned int *num_planes,
		unsigned int sizes[], struct device *alloc_devs[])
{
	sizes[0] = GO7007_BUF_SIZE;
	*num_planes = 1;

	if (*num_buffers < 2)
		*num_buffers = 2;

	return 0;
}
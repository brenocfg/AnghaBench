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
struct nvme_dev {int num_vecs; } ;

/* Variables and functions */

__attribute__((used)) static int queue_irq_offset(struct nvme_dev *dev)
{
	/* if we have more than 1 vec, admin queue offsets us by 1 */
	if (dev->num_vecs > 1)
		return 1;

	return 0;
}
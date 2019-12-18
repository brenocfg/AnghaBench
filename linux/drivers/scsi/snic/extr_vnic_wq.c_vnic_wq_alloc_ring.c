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
struct vnic_wq {int /*<<< orphan*/  ring; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int svnic_dev_alloc_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static inline int vnic_wq_alloc_ring(struct vnic_dev *vdev, struct vnic_wq *wq,
	unsigned int index, unsigned int desc_count, unsigned int desc_size)
{
	return svnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count,
					 desc_size);
}
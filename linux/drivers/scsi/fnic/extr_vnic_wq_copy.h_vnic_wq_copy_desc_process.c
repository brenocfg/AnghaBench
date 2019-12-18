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
typedef  int u16 ;
struct TYPE_2__ {int desc_count; unsigned int desc_avail; } ;
struct vnic_wq_copy {int to_clean_index; TYPE_1__ ring; } ;

/* Variables and functions */

__attribute__((used)) static inline void vnic_wq_copy_desc_process(struct vnic_wq_copy *wq, u16 index)
{
	unsigned int cnt;

	if (wq->to_clean_index <= index)
		cnt = (index - wq->to_clean_index) + 1;
	else
		cnt = wq->ring.desc_count - wq->to_clean_index + index + 1;

	wq->to_clean_index = ((index + 1) % wq->ring.desc_count);
	wq->ring.desc_avail += cnt;

}
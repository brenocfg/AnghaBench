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
struct __vxge_hw_ring {int dummy; } ;

/* Variables and functions */
 int VXGE_HW_RXSYNC_FREQ_CNT ; 
 int /*<<< orphan*/  vxge_hw_ring_rxd_post_post (struct __vxge_hw_ring*,void*) ; 
 int /*<<< orphan*/  vxge_hw_ring_rxd_post_post_wmb (struct __vxge_hw_ring*,void*) ; 

__attribute__((used)) static inline void vxge_post(int *dtr_cnt, void **first_dtr,
			     void *post_dtr, struct __vxge_hw_ring *ringh)
{
	int dtr_count = *dtr_cnt;
	if ((*dtr_cnt % VXGE_HW_RXSYNC_FREQ_CNT) == 0) {
		if (*first_dtr)
			vxge_hw_ring_rxd_post_post_wmb(ringh, *first_dtr);
		*first_dtr = post_dtr;
	} else
		vxge_hw_ring_rxd_post_post(ringh, post_dtr);
	dtr_count++;
	*dtr_cnt = dtr_count;
}
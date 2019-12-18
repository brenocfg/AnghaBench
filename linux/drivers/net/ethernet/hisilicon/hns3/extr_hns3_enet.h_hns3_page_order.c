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
struct hns3_enet_ring {int buf_size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

__attribute__((used)) static inline unsigned int hns3_page_order(struct hns3_enet_ring *ring)
{
#if (PAGE_SIZE < 8192)
	if (ring->buf_size > (PAGE_SIZE / 2))
		return 1;
#endif
	return 0;
}
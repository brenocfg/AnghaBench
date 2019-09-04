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
struct hns3_enet_ring {int desc_num; } ;

/* Variables and functions */

__attribute__((used)) static inline int ring_dist(struct hns3_enet_ring *ring, int begin, int end)
{
	return (end - begin + ring->desc_num) % ring->desc_num;
}
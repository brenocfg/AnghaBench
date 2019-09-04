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
struct hns3_enet_ring {int next_to_use; int next_to_clean; int desc_num; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int is_valid_clean_head(struct hns3_enet_ring *ring, int h)
{
	int u = ring->next_to_use;
	int c = ring->next_to_clean;

	if (unlikely(h > ring->desc_num))
		return 0;

	return u > c ? (h > c && h <= u) : (h > c || h <= u);
}
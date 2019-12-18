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
struct hclgevf_cmq_ring {int next_to_clean; int next_to_use; int desc_num; } ;

/* Variables and functions */

__attribute__((used)) static int hclgevf_ring_space(struct hclgevf_cmq_ring *ring)
{
	int ntc = ring->next_to_clean;
	int ntu = ring->next_to_use;
	int used;

	used = (ntu - ntc + ring->desc_num) % ring->desc_num;

	return ring->desc_num - used - 1;
}
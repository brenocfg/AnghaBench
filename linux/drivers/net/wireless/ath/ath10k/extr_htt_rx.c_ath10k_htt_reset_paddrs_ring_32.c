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
struct TYPE_2__ {scalar_t__* paddrs_ring_32; } ;
struct ath10k_htt {TYPE_1__ rx_ring; } ;

/* Variables and functions */

__attribute__((used)) static void ath10k_htt_reset_paddrs_ring_32(struct ath10k_htt *htt, int idx)
{
	htt->rx_ring.paddrs_ring_32[idx] = 0;
}
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
struct ath10k_htt {TYPE_1__* rx_ops; } ;
struct TYPE_2__ {void* (* htt_get_vaddr_ring ) (struct ath10k_htt*) ;} ;

/* Variables and functions */
 void* stub1 (struct ath10k_htt*) ; 

__attribute__((used)) static inline void *ath10k_htt_get_vaddr_ring(struct ath10k_htt *htt)
{
	if (!htt->rx_ops->htt_get_vaddr_ring)
		return NULL;

	return htt->rx_ops->htt_get_vaddr_ring(htt);
}
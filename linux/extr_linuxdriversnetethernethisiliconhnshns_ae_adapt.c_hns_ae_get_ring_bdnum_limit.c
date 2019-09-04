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
typedef  int /*<<< orphan*/  u32 ;
struct hnae_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_RCB_RING_MAX_PENDING_BD ; 

__attribute__((used)) static void hns_ae_get_ring_bdnum_limit(struct hnae_queue *queue,
					u32 *uplimit)
{
	*uplimit = HNS_RCB_RING_MAX_PENDING_BD;
}
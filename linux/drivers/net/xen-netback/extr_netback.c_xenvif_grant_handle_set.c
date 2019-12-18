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
typedef  size_t u16 ;
struct xenvif_queue {scalar_t__* grant_tx_handle; TYPE_1__* vif; } ;
typedef  scalar_t__ grant_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ NETBACK_INVALID_HANDLE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void xenvif_grant_handle_set(struct xenvif_queue *queue,
					   u16 pending_idx,
					   grant_handle_t handle)
{
	if (unlikely(queue->grant_tx_handle[pending_idx] !=
		     NETBACK_INVALID_HANDLE)) {
		netdev_err(queue->vif->dev,
			   "Trying to overwrite active handle! pending_idx: 0x%x\n",
			   pending_idx);
		BUG();
	}
	queue->grant_tx_handle[pending_idx] = handle;
}
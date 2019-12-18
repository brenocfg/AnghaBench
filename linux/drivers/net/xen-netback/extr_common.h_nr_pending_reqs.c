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
struct xenvif_queue {scalar_t__ pending_cons; scalar_t__ pending_prod; } ;
typedef  scalar_t__ pending_ring_idx_t ;

/* Variables and functions */
 scalar_t__ MAX_PENDING_REQS ; 

__attribute__((used)) static inline pending_ring_idx_t nr_pending_reqs(struct xenvif_queue *queue)
{
	return MAX_PENDING_REQS -
		queue->pending_prod + queue->pending_cons;
}
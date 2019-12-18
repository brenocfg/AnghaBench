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
typedef  int u8 ;
struct wil_status_ring {int elem_size; int swhead; scalar_t__ va; } ;
struct wil_ring_tx_status {int desc_ready; } ;

/* Variables and functions */
 int TX_STATUS_DESC_READY_POS ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline void
wil_get_next_tx_status_msg(struct wil_status_ring *sring, u8 *dr_bit,
			   struct wil_ring_tx_status *msg)
{
	struct wil_ring_tx_status *_msg = (struct wil_ring_tx_status *)
		(sring->va + (sring->elem_size * sring->swhead));

	*dr_bit = _msg->desc_ready >> TX_STATUS_DESC_READY_POS;
	/* make sure dr_bit is read before the rest of status msg */
	rmb();
	*msg = *_msg;
}
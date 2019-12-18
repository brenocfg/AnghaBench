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
typedef  int /*<<< orphan*/  u8 ;
struct wil_status_ring {int elem_size; int swhead; scalar_t__ va; } ;
struct wil_rx_status_compressed {int /*<<< orphan*/  d0; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_GET_BITS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline
void wil_get_next_rx_status_msg(struct wil_status_ring *sring, u8 *dr_bit,
				void *msg)
{
	struct wil_rx_status_compressed *_msg;

	_msg = (struct wil_rx_status_compressed *)
		(sring->va + (sring->elem_size * sring->swhead));
	*dr_bit = WIL_GET_BITS(_msg->d0, 31, 31);
	/* make sure dr_bit is read before the rest of status msg */
	rmb();
	memcpy(msg, (void *)_msg, sring->elem_size);
}
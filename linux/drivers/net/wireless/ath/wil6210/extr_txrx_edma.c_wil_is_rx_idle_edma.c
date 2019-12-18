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
typedef  scalar_t__ u8 ;
struct wil_status_ring {scalar_t__ desc_rdy_pol; int /*<<< orphan*/  va; } ;
struct wil_rx_status_extended {int dummy; } ;
struct wil6210_priv {int num_rx_status_rings; struct wil_status_ring* srings; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_get_next_rx_status_msg (struct wil_status_ring*,scalar_t__*,void*) ; 

__attribute__((used)) static bool wil_is_rx_idle_edma(struct wil6210_priv *wil)
{
	struct wil_status_ring *sring;
	struct wil_rx_status_extended msg1;
	void *msg = &msg1;
	u8 dr_bit;
	int i;

	for (i = 0; i < wil->num_rx_status_rings; i++) {
		sring = &wil->srings[i];
		if (!sring->va)
			continue;

		wil_get_next_rx_status_msg(sring, &dr_bit, msg);

		/* Check if there are unhandled RX status messages */
		if (dr_bit == sring->desc_rdy_pol)
			return false;
	}

	return true;
}
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
struct wil_ring {int dummy; } ;
struct wil6210_priv {int num_rx_status_rings; int /*<<< orphan*/ * srings; struct wil_ring ring_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_free_rx_buff_arr (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_ring_free_edma (struct wil6210_priv*,struct wil_ring*) ; 
 int /*<<< orphan*/  wil_rx_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_sring_free (struct wil6210_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wil_rx_fini_edma(struct wil6210_priv *wil)
{
	struct wil_ring *ring = &wil->ring_rx;
	int i;

	wil_dbg_misc(wil, "rx_fini_edma\n");

	wil_ring_free_edma(wil, ring);

	for (i = 0; i < wil->num_rx_status_rings; i++) {
		wil_rx_data_free(&wil->srings[i]);
		wil_sring_free(wil, &wil->srings[i]);
	}

	wil_free_rx_buff_arr(wil);
}
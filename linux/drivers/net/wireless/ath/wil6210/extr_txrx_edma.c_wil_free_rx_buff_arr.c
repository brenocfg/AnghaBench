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
struct wil_ring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buff_arr; } ;
struct wil6210_priv {TYPE_1__ rx_buff_mgmt; struct wil_ring ring_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_move_all_rx_buff_to_free_list (struct wil6210_priv*,struct wil_ring*) ; 

__attribute__((used)) static void wil_free_rx_buff_arr(struct wil6210_priv *wil)
{
	struct wil_ring *ring = &wil->ring_rx;

	if (!wil->rx_buff_mgmt.buff_arr)
		return;

	/* Move all the buffers to the free list in case active list is
	 * not empty in order to release all SKBs before deleting the array
	 */
	wil_move_all_rx_buff_to_free_list(wil, ring);

	kfree(wil->rx_buff_mgmt.buff_arr);
	wil->rx_buff_mgmt.buff_arr = NULL;
}
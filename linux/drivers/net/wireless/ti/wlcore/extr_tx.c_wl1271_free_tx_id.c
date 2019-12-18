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
struct wl1271 {scalar_t__ tx_frames_cnt; scalar_t__ num_tx_desc; int /*<<< orphan*/ ** tx_frames; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_frames_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_FW_TX_BUSY ; 
 scalar_t__ __test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void wl1271_free_tx_id(struct wl1271 *wl, int id)
{
	if (__test_and_clear_bit(id, wl->tx_frames_map)) {
		if (unlikely(wl->tx_frames_cnt == wl->num_tx_desc))
			clear_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags);

		wl->tx_frames[id] = NULL;
		wl->tx_frames_cnt--;
	}
}
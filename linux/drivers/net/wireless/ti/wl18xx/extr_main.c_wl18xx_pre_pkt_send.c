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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;
struct wl1271_tx_hw_descr {TYPE_1__ wl18xx_mem; } ;
struct wl1271 {int quirks; scalar_t__ aggr_buf; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL12XX_BUS_BLOCK_SIZE ; 
 int /*<<< orphan*/  WL18XX_TX_CTRL_NOT_PADDED ; 
 int WLCORE_QUIRK_TX_PAD_LAST_FRAME ; 

__attribute__((used)) static u32 wl18xx_pre_pkt_send(struct wl1271 *wl,
			       u32 buf_offset, u32 last_len)
{
	if (wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME) {
		struct wl1271_tx_hw_descr *last_desc;

		/* get the last TX HW descriptor written to the aggr buf */
		last_desc = (struct wl1271_tx_hw_descr *)(wl->aggr_buf +
							buf_offset - last_len);

		/* the last frame is padded up to an SDIO block */
		last_desc->wl18xx_mem.ctrl &= ~WL18XX_TX_CTRL_NOT_PADDED;
		return ALIGN(buf_offset, WL12XX_BUS_BLOCK_SIZE);
	}

	/* no modifications */
	return buf_offset;
}
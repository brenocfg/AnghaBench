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
struct TYPE_2__ {int /*<<< orphan*/  total_mem_blocks; scalar_t__ ctrl; } ;
struct wl1271_tx_hw_descr {TYPE_1__ wl18xx_mem; int /*<<< orphan*/  life_time; int /*<<< orphan*/  length; int /*<<< orphan*/  hlid; } ;
struct wl1271 {int quirks; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 scalar_t__ WL18XX_TX_CTRL_NOT_PADDED ; 
 int WLCORE_QUIRK_TX_PAD_LAST_FRAME ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wl18xx_set_tx_desc_data_len(struct wl1271 *wl, struct wl1271_tx_hw_descr *desc,
			    struct sk_buff *skb)
{
	desc->length = cpu_to_le16(skb->len);

	/* if only the last frame is to be padded, we unset this bit on Tx */
	if (wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME)
		desc->wl18xx_mem.ctrl = WL18XX_TX_CTRL_NOT_PADDED;
	else
		desc->wl18xx_mem.ctrl = 0;

	wl1271_debug(DEBUG_TX, "tx_fill_hdr: hlid: %d "
		     "len: %d life: %d mem: %d", desc->hlid,
		     le16_to_cpu(desc->length),
		     le16_to_cpu(desc->life_time),
		     desc->wl18xx_mem.total_mem_blocks);
}
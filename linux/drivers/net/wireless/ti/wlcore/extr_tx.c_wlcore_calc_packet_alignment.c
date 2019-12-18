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
struct wl1271 {int quirks; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL1271_TX_ALIGN_TO ; 
 int /*<<< orphan*/  WL12XX_BUS_BLOCK_SIZE ; 
 int WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN ; 
 int WLCORE_QUIRK_TX_PAD_LAST_FRAME ; 

unsigned int wlcore_calc_packet_alignment(struct wl1271 *wl,
					  unsigned int packet_length)
{
	if ((wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME) ||
	    !(wl->quirks & WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN))
		return ALIGN(packet_length, WL1271_TX_ALIGN_TO);
	else
		return ALIGN(packet_length, WL12XX_BUS_BLOCK_SIZE);
}
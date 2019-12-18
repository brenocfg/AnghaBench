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

/* Variables and functions */
#define  WIL_RX_CB_MODE_DMG 130 
#define  WIL_RX_CB_MODE_EDMG 129 
#define  WIL_RX_CB_MODE_WIDE 128 

__attribute__((used)) static int wil_rx_cb_mode_to_n_bonded(u8 cb_mode)
{
	switch (cb_mode) {
	case WIL_RX_CB_MODE_DMG:
	case WIL_RX_CB_MODE_EDMG:
		return 1;
	case WIL_RX_CB_MODE_WIDE:
		return 2;
	default:
		return 1;
	}
}
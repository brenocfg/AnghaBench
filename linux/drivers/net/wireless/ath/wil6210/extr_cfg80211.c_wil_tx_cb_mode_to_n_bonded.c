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
#define  WMI_TX_MODE_DMG 130 
#define  WMI_TX_MODE_EDMG_CB1 129 
#define  WMI_TX_MODE_EDMG_CB2 128 

__attribute__((used)) static int wil_tx_cb_mode_to_n_bonded(u8 cb_mode)
{
	switch (cb_mode) {
	case WMI_TX_MODE_DMG:
	case WMI_TX_MODE_EDMG_CB1:
		return 1;
	case WMI_TX_MODE_EDMG_CB2:
		return 2;
	default:
		return 1;
	}
}
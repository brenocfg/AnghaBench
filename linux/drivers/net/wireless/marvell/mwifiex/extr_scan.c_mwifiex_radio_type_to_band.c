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
 int BAND_A ; 
 int BAND_G ; 
#define  HostCmd_SCAN_RADIO_TYPE_A 129 
#define  HostCmd_SCAN_RADIO_TYPE_BG 128 

__attribute__((used)) static u8
mwifiex_radio_type_to_band(u8 radio_type)
{
	switch (radio_type) {
	case HostCmd_SCAN_RADIO_TYPE_A:
		return BAND_A;
	case HostCmd_SCAN_RADIO_TYPE_BG:
	default:
		return BAND_G;
	}
}
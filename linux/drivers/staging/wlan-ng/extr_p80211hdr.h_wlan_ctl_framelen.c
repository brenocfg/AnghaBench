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
typedef  int u16 ;

/* Variables and functions */
#define  WLAN_FSTYPE_ACK 135 
#define  WLAN_FSTYPE_BLOCKACK 134 
#define  WLAN_FSTYPE_BLOCKACKREQ 133 
#define  WLAN_FSTYPE_CFEND 132 
#define  WLAN_FSTYPE_CFENDCFACK 131 
#define  WLAN_FSTYPE_CTS 130 
#define  WLAN_FSTYPE_PSPOLL 129 
#define  WLAN_FSTYPE_RTS 128 

__attribute__((used)) static inline u16 wlan_ctl_framelen(u16 fstype)
{
	switch (fstype)	{
	case WLAN_FSTYPE_BLOCKACKREQ:
		return 24;
	case WLAN_FSTYPE_BLOCKACK:
		return 152;
	case WLAN_FSTYPE_PSPOLL:
	case WLAN_FSTYPE_RTS:
	case WLAN_FSTYPE_CFEND:
	case WLAN_FSTYPE_CFENDCFACK:
		return 20;
	case WLAN_FSTYPE_CTS:
	case WLAN_FSTYPE_ACK:
		return 14;
	default:
		return 4;
	}
}
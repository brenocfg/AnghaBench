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
#define  TDLS_CHAN_SWITCHING 131 
#define  TDLS_IN_BASE_CHAN 130 
#define  TDLS_IN_OFF_CHAN 129 
#define  TDLS_SETUP_COMPLETE 128 

__attribute__((used)) static inline u8 mwifiex_is_tdls_link_setup(u8 status)
{
	switch (status) {
	case TDLS_SETUP_COMPLETE:
	case TDLS_CHAN_SWITCHING:
	case TDLS_IN_BASE_CHAN:
	case TDLS_IN_OFF_CHAN:
		return true;
	default:
		break;
	}

	return false;
}
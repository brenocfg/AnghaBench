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
typedef  enum htt_security_types { ____Placeholder_htt_security_types } htt_security_types ;

/* Variables and functions */
#define  HTT_SECURITY_AES_CCMP 130 
#define  HTT_SECURITY_TKIP 129 
#define  HTT_SECURITY_TKIP_NOMIC 128 

__attribute__((used)) static int ath10k_htt_rx_pn_len(enum htt_security_types sec_type)
{
	switch (sec_type) {
	case HTT_SECURITY_TKIP:
	case HTT_SECURITY_TKIP_NOMIC:
	case HTT_SECURITY_AES_CCMP:
		return 48;
	default:
		return 0;
	}
}
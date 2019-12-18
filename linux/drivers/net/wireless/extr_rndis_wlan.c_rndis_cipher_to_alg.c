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
typedef  int u32 ;

/* Variables and functions */
 int RNDIS_WLAN_ALG_CCMP ; 
 int RNDIS_WLAN_ALG_NONE ; 
 int RNDIS_WLAN_ALG_TKIP ; 
 int RNDIS_WLAN_ALG_WEP ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 

__attribute__((used)) static int rndis_cipher_to_alg(u32 cipher)
{
	switch (cipher) {
	default:
		return RNDIS_WLAN_ALG_NONE;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		return RNDIS_WLAN_ALG_WEP;
	case WLAN_CIPHER_SUITE_TKIP:
		return RNDIS_WLAN_ALG_TKIP;
	case WLAN_CIPHER_SUITE_CCMP:
		return RNDIS_WLAN_ALG_CCMP;
	}
}
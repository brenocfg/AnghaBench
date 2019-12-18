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
typedef  enum mt7615_cipher_type { ____Placeholder_mt7615_cipher_type } mt7615_cipher_type ;

/* Variables and functions */
 int MT_CIPHER_AES_CCMP ; 
 int MT_CIPHER_BIP_CMAC_128 ; 
 int MT_CIPHER_CCMP_256 ; 
 int MT_CIPHER_GCMP ; 
 int MT_CIPHER_GCMP_256 ; 
 int MT_CIPHER_NONE ; 
 int MT_CIPHER_TKIP ; 
 int MT_CIPHER_WAPI ; 
 int MT_CIPHER_WEP104 ; 
 int MT_CIPHER_WEP40 ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 136 
#define  WLAN_CIPHER_SUITE_CCMP 135 
#define  WLAN_CIPHER_SUITE_CCMP_256 134 
#define  WLAN_CIPHER_SUITE_GCMP 133 
#define  WLAN_CIPHER_SUITE_GCMP_256 132 
#define  WLAN_CIPHER_SUITE_SMS4 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 

__attribute__((used)) static enum mt7615_cipher_type
mt7615_mac_get_cipher(int cipher)
{
	switch (cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
		return MT_CIPHER_WEP40;
	case WLAN_CIPHER_SUITE_WEP104:
		return MT_CIPHER_WEP104;
	case WLAN_CIPHER_SUITE_TKIP:
		return MT_CIPHER_TKIP;
	case WLAN_CIPHER_SUITE_AES_CMAC:
		return MT_CIPHER_BIP_CMAC_128;
	case WLAN_CIPHER_SUITE_CCMP:
		return MT_CIPHER_AES_CCMP;
	case WLAN_CIPHER_SUITE_CCMP_256:
		return MT_CIPHER_CCMP_256;
	case WLAN_CIPHER_SUITE_GCMP:
		return MT_CIPHER_GCMP;
	case WLAN_CIPHER_SUITE_GCMP_256:
		return MT_CIPHER_GCMP_256;
	case WLAN_CIPHER_SUITE_SMS4:
		return MT_CIPHER_WAPI;
	default:
		return MT_CIPHER_NONE;
	}
}
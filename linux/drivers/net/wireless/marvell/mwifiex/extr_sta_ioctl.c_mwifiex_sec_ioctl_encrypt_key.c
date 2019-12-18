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
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_encrypt_key {scalar_t__ key_len; scalar_t__ is_wapi_key; } ;

/* Variables and functions */
 scalar_t__ WLAN_KEY_LEN_WEP104 ; 
 int mwifiex_sec_ioctl_set_wapi_key (struct mwifiex_private*,struct mwifiex_ds_encrypt_key*) ; 
 int mwifiex_sec_ioctl_set_wep_key (struct mwifiex_private*,struct mwifiex_ds_encrypt_key*) ; 
 int mwifiex_sec_ioctl_set_wpa_key (struct mwifiex_private*,struct mwifiex_ds_encrypt_key*) ; 

__attribute__((used)) static int
mwifiex_sec_ioctl_encrypt_key(struct mwifiex_private *priv,
			      struct mwifiex_ds_encrypt_key *encrypt_key)
{
	int status;

	if (encrypt_key->is_wapi_key)
		status = mwifiex_sec_ioctl_set_wapi_key(priv, encrypt_key);
	else if (encrypt_key->key_len > WLAN_KEY_LEN_WEP104)
		status = mwifiex_sec_ioctl_set_wpa_key(priv, encrypt_key);
	else
		status = mwifiex_sec_ioctl_set_wep_key(priv, encrypt_key);
	return status;
}
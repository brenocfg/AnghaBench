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
struct rt2x00lib_crypto {int dummy; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int rt61pci_config_shared_key(struct rt2x00_dev *rt2x00dev,
				     struct rt2x00lib_crypto *crypto,
				     struct ieee80211_key_conf *key)
{
	/*
	 * Let the software handle the shared keys,
	 * since the hardware decryption does not work reliably,
	 * because the firmware does not know the key's keyidx.
	 */
	return -EOPNOTSUPP;
}
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
struct ieee80211_key_conf {int dummy; } ;
typedef  enum cipher { ____Placeholder_cipher } cipher ;

/* Variables and functions */
 int CIPHER_NONE ; 

__attribute__((used)) static inline enum cipher rt2x00crypto_key_to_cipher(struct ieee80211_key_conf *key)
{
	return CIPHER_NONE;
}
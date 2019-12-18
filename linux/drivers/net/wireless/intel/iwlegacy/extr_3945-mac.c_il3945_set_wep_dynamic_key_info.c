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
typedef  int /*<<< orphan*/  u8 ;
struct il_priv {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
il3945_set_wep_dynamic_key_info(struct il_priv *il,
				struct ieee80211_key_conf *keyconf, u8 sta_id)
{
	return -EOPNOTSUPP;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_key_conf {int dummy; } ;
struct ath10k_vif {scalar_t__ nohwcrypt; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  install_key_done; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int ath10k_send_key (struct ath10k_vif*,struct ieee80211_key_conf*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_install_key(struct ath10k_vif *arvif,
			      struct ieee80211_key_conf *key,
			      enum set_key_cmd cmd,
			      const u8 *macaddr, u32 flags)
{
	struct ath10k *ar = arvif->ar;
	int ret;
	unsigned long time_left;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->install_key_done);

	if (arvif->nohwcrypt)
		return 1;

	ret = ath10k_send_key(arvif, key, cmd, macaddr, flags);
	if (ret)
		return ret;

	time_left = wait_for_completion_timeout(&ar->install_key_done, 3 * HZ);
	if (time_left == 0)
		return -ETIMEDOUT;

	return 0;
}
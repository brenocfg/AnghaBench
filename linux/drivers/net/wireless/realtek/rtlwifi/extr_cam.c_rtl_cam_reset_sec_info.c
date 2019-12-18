#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int use_defaultkey; int /*<<< orphan*/ * pairwise_key; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key_buf; void* group_enc_algorithm; void* pairwise_enc_algorithm; } ;
struct rtl_priv {TYPE_1__ sec; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int KEY_BUF_SIZE ; 
 int MAX_KEY_LEN ; 
 void* NO_ENCRYPTION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_cam_reset_sec_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->sec.use_defaultkey = false;
	rtlpriv->sec.pairwise_enc_algorithm = NO_ENCRYPTION;
	rtlpriv->sec.group_enc_algorithm = NO_ENCRYPTION;
	memset(rtlpriv->sec.key_buf, 0, KEY_BUF_SIZE * MAX_KEY_LEN);
	memset(rtlpriv->sec.key_len, 0, KEY_BUF_SIZE);
	rtlpriv->sec.pairwise_key = NULL;
}
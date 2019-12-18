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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_USER_RTS_THRESHOLD ; 
 int ar5523_config (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ar5523_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct ar5523 *ar = hw->priv;
	int ret;

	ar5523_dbg(ar, "set_rts_threshold called\n");
	mutex_lock(&ar->mutex);

	ret = ar5523_config(ar, CFG_USER_RTS_THRESHOLD, value);

	mutex_unlock(&ar->mutex);
	return ret;
}
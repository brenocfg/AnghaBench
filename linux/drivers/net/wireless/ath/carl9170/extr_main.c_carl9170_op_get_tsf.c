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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  tsf ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ar9170* priv; } ;
struct carl9170_tsf_rsp {int /*<<< orphan*/  tsf_64; } ;
struct ar9170 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_READ_TSF ; 
 scalar_t__ WARN_ON (int) ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct carl9170_tsf_rsp*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 carl9170_op_get_tsf(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif)
{
	struct ar9170 *ar = hw->priv;
	struct carl9170_tsf_rsp tsf;
	int err;

	mutex_lock(&ar->mutex);
	err = carl9170_exec_cmd(ar, CARL9170_CMD_READ_TSF,
				0, NULL, sizeof(tsf), &tsf);
	mutex_unlock(&ar->mutex);
	if (WARN_ON(err))
		return 0;

	return le64_to_cpu(tsf.tsf_64);
}
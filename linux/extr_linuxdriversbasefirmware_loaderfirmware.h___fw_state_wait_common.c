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
struct fw_state {scalar_t__ status; int /*<<< orphan*/  completion; } ;
struct fw_priv {struct fw_state fw_st; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETIMEDOUT ; 
 scalar_t__ FW_STATUS_ABORTED ; 
 long wait_for_completion_killable_timeout (int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static inline int __fw_state_wait_common(struct fw_priv *fw_priv, long timeout)
{
	struct fw_state *fw_st = &fw_priv->fw_st;
	long ret;

	ret = wait_for_completion_killable_timeout(&fw_st->completion, timeout);
	if (ret != 0 && fw_st->status == FW_STATUS_ABORTED)
		return -ENOENT;
	if (!ret)
		return -ETIMEDOUT;

	return ret < 0 ? ret : 0;
}
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
struct qed_resc_unlock_params {int sleep_b4_retry; int resource; int /*<<< orphan*/  retry_interval; int /*<<< orphan*/  retry_num; int /*<<< orphan*/  timeout; } ;
struct qed_resc_lock_params {int sleep_b4_retry; int resource; int /*<<< orphan*/  retry_interval; int /*<<< orphan*/  retry_num; int /*<<< orphan*/  timeout; } ;
typedef  enum qed_resc_lock { ____Placeholder_qed_resc_lock } qed_resc_lock ;

/* Variables and functions */
 int /*<<< orphan*/  QED_MCP_RESC_LOCK_RETRY_CNT_DFLT ; 
 int /*<<< orphan*/  QED_MCP_RESC_LOCK_RETRY_VAL_DFLT ; 
 int /*<<< orphan*/  QED_MCP_RESC_LOCK_TO_NONE ; 
 int /*<<< orphan*/  memset (struct qed_resc_unlock_params*,int /*<<< orphan*/ ,int) ; 

void qed_mcp_resc_lock_default_init(struct qed_resc_lock_params *p_lock,
				    struct qed_resc_unlock_params *p_unlock,
				    enum qed_resc_lock
				    resource, bool b_is_permanent)
{
	if (p_lock) {
		memset(p_lock, 0, sizeof(*p_lock));

		/* Permanent resources don't require aging, and there's no
		 * point in trying to acquire them more than once since it's
		 * unexpected another entity would release them.
		 */
		if (b_is_permanent) {
			p_lock->timeout = QED_MCP_RESC_LOCK_TO_NONE;
		} else {
			p_lock->retry_num = QED_MCP_RESC_LOCK_RETRY_CNT_DFLT;
			p_lock->retry_interval =
			    QED_MCP_RESC_LOCK_RETRY_VAL_DFLT;
			p_lock->sleep_b4_retry = true;
		}

		p_lock->resource = resource;
	}

	if (p_unlock) {
		memset(p_unlock, 0, sizeof(*p_unlock));
		p_unlock->resource = resource;
	}
}
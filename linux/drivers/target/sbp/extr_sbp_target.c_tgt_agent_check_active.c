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
struct sbp_target_agent {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ AGENT_STATE_ACTIVE ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool tgt_agent_check_active(struct sbp_target_agent *agent)
{
	bool active;

	spin_lock_bh(&agent->lock);
	active = (agent->state == AGENT_STATE_ACTIVE);
	spin_unlock_bh(&agent->lock);

	return active;
}
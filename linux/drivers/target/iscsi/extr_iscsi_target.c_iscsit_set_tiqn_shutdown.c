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
struct iscsi_tiqn {scalar_t__ tiqn_state; int /*<<< orphan*/  tiqn_state_lock; } ;

/* Variables and functions */
 scalar_t__ TIQN_STATE_ACTIVE ; 
 scalar_t__ TIQN_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_set_tiqn_shutdown(struct iscsi_tiqn *tiqn)
{
	spin_lock(&tiqn->tiqn_state_lock);
	if (tiqn->tiqn_state == TIQN_STATE_ACTIVE) {
		tiqn->tiqn_state = TIQN_STATE_SHUTDOWN;
		spin_unlock(&tiqn->tiqn_state_lock);
		return 0;
	}
	spin_unlock(&tiqn->tiqn_state_lock);

	return -1;
}
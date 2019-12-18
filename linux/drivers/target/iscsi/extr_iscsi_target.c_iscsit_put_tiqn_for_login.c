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
struct iscsi_tiqn {int /*<<< orphan*/  tiqn_state_lock; int /*<<< orphan*/  tiqn_access_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iscsit_put_tiqn_for_login(struct iscsi_tiqn *tiqn)
{
	spin_lock(&tiqn->tiqn_state_lock);
	tiqn->tiqn_access_count--;
	spin_unlock(&tiqn->tiqn_state_lock);
}
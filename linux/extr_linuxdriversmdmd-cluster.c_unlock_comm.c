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
struct md_cluster_info {int /*<<< orphan*/  wait; int /*<<< orphan*/  state; TYPE_1__* token_lockres; int /*<<< orphan*/  recv_mutex; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_EX ; 
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_unlock_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_comm(struct md_cluster_info *cinfo)
{
	WARN_ON(cinfo->token_lockres->mode != DLM_LOCK_EX);
	mutex_unlock(&cinfo->recv_mutex);
	dlm_unlock_sync(cinfo->token_lockres);
	clear_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state);
	wake_up(&cinfo->wait);
}
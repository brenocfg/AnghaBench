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
struct zfcp_erp_action {struct zfcp_adapter* adapter; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_ready_wq; int /*<<< orphan*/  erp_ready_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_run (char*,struct zfcp_erp_action*) ; 

__attribute__((used)) static void zfcp_erp_action_ready(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;

	list_move(&act->list, &act->adapter->erp_ready_head);
	zfcp_dbf_rec_run("erardy1", act);
	wake_up(&adapter->erp_ready_wq);
	zfcp_dbf_rec_run("erardy2", act);
}
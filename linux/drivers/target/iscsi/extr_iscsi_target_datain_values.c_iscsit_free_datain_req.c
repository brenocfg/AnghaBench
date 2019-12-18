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
struct iscsi_datain_req {int /*<<< orphan*/  cmd_datain_node; } ;
struct iscsi_cmd {int /*<<< orphan*/  datain_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct iscsi_datain_req*) ; 
 int /*<<< orphan*/  lio_dr_cache ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iscsit_free_datain_req(struct iscsi_cmd *cmd, struct iscsi_datain_req *dr)
{
	spin_lock(&cmd->datain_lock);
	list_del(&dr->cmd_datain_node);
	spin_unlock(&cmd->datain_lock);

	kmem_cache_free(lio_dr_cache, dr);
}
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
struct iscsi_r2t {int /*<<< orphan*/  r2t_list; } ;
struct iscsi_cmd {int /*<<< orphan*/  r2t_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct iscsi_r2t*) ; 
 int /*<<< orphan*/  lio_r2t_cache ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iscsit_free_r2t(struct iscsi_r2t *r2t, struct iscsi_cmd *cmd)
{
	lockdep_assert_held(&cmd->r2t_lock);

	list_del(&r2t->r2t_list);
	kmem_cache_free(lio_r2t_cache, r2t);
}
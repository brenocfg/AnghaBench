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
struct tb {int /*<<< orphan*/  dev; } ;
struct icm {int veto; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static void icm_veto_end(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	if (icm->veto) {
		icm->veto = false;
		/* Allow the domain suspend now */
		pm_runtime_mark_last_busy(&tb->dev);
		pm_runtime_put_autosuspend(&tb->dev);
	}
}
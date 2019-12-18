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
struct tb {int /*<<< orphan*/  wq; } ;
struct icm {int /*<<< orphan*/  rescan_work; } ;

/* Variables and functions */
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static void icm_postpone_rescan(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	if (delayed_work_pending(&icm->rescan_work))
		mod_delayed_work(tb->wq, &icm->rescan_work,
				 msecs_to_jiffies(500));
}
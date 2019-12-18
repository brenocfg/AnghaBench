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
struct vmballoon {int /*<<< orphan*/  dwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMW_BALLOON_STAT_DOORBELL ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 int /*<<< orphan*/  vmballoon_stats_gen_inc (struct vmballoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmballoon_doorbell(void *client_data)
{
	struct vmballoon *b = client_data;

	vmballoon_stats_gen_inc(b, VMW_BALLOON_STAT_DOORBELL);

	mod_delayed_work(system_freezable_wq, &b->dwork, 0);
}
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
struct ntb_msit_ctx {int /*<<< orphan*/  setup_work; int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ntb_msit_link_event(void *ctx)
{
	struct ntb_msit_ctx *nm = ctx;

	if (!ntb_link_is_up(nm->ntb, NULL, NULL))
		return;

	schedule_work(&nm->setup_work);
}
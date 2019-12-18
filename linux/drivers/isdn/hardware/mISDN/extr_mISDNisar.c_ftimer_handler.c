#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; } ;
struct isar_ch {TYPE_2__ bch; TYPE_1__* is; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_FTI_RUN ; 
 int /*<<< orphan*/  FLG_LL_CONN ; 
 int /*<<< orphan*/  HW_MOD_CONNECT ; 
 struct isar_ch* ch ; 
 int /*<<< orphan*/  deliver_status (struct isar_ch*,int /*<<< orphan*/ ) ; 
 struct isar_ch* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftimer ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ftimer_handler(struct timer_list *t)
{
	struct isar_ch *ch = from_timer(ch, t, ftimer);

	pr_debug("%s: ftimer flags %lx\n", ch->is->name, ch->bch.Flags);
	test_and_clear_bit(FLG_FTI_RUN, &ch->bch.Flags);
	if (test_and_clear_bit(FLG_LL_CONN, &ch->bch.Flags))
		deliver_status(ch, HW_MOD_CONNECT);
}
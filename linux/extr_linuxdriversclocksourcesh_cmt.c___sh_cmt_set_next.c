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
struct sh_cmt_channel {unsigned long max_match_value; unsigned long next_match_value; int /*<<< orphan*/  index; TYPE_2__* cmt; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_clock_event_program_verify (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sh_cmt_set_next(struct sh_cmt_channel *ch, unsigned long delta)
{
	if (delta > ch->max_match_value)
		dev_warn(&ch->cmt->pdev->dev, "ch%u: delta out of range\n",
			 ch->index);

	ch->next_match_value = delta;
	sh_cmt_clock_event_program_verify(ch, 0);
}
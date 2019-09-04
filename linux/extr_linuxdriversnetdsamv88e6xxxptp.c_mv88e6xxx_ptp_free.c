#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mv88e6xxx_chip {int /*<<< orphan*/ * ptp_clock; int /*<<< orphan*/  tai_event_work; TYPE_3__* info; int /*<<< orphan*/  overflow_work; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {TYPE_1__* ptp_ops; } ;
struct TYPE_4__ {scalar_t__ event_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void mv88e6xxx_ptp_free(struct mv88e6xxx_chip *chip)
{
	if (chip->ptp_clock) {
		cancel_delayed_work_sync(&chip->overflow_work);
		if (chip->info->ops->ptp_ops->event_work)
			cancel_delayed_work_sync(&chip->tai_event_work);

		ptp_clock_unregister(chip->ptp_clock);
		chip->ptp_clock = NULL;
	}
}
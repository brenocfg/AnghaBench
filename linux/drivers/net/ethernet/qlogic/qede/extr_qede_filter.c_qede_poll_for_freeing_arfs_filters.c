#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qede_dev {TYPE_1__* arfs; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int QEDE_ARFS_POLL_COUNT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qede_process_arfs_filters (struct qede_dev*,int) ; 

void qede_poll_for_freeing_arfs_filters(struct qede_dev *edev)
{
	int count = QEDE_ARFS_POLL_COUNT;

	while (count) {
		qede_process_arfs_filters(edev, false);

		if (!edev->arfs->filter_count)
			break;

		msleep(100);
		count--;
	}

	if (!count) {
		DP_NOTICE(edev, "Timeout in polling for arfs filter free\n");

		/* Something is terribly wrong, free forcefully */
		qede_process_arfs_filters(edev, true);
	}
}
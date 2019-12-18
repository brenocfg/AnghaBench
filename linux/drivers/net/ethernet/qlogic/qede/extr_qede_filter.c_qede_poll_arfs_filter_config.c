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
struct qede_dev {int dummy; } ;
struct qede_arfs_fltr_node {int fw_rc; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EIO ; 
 int QEDE_ARFS_POLL_COUNT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qede_dequeue_fltr_and_config_searcher (struct qede_dev*,struct qede_arfs_fltr_node*) ; 

__attribute__((used)) static int
qede_poll_arfs_filter_config(struct qede_dev *edev,
			     struct qede_arfs_fltr_node *fltr)
{
	int count = QEDE_ARFS_POLL_COUNT;

	while (fltr->used && count) {
		msleep(20);
		count--;
	}

	if (count == 0 || fltr->fw_rc) {
		DP_NOTICE(edev, "Timeout in polling filter config\n");
		qede_dequeue_fltr_and_config_searcher(edev, fltr);
		return -EIO;
	}

	return fltr->fw_rc;
}
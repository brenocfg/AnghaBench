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
struct qed_ll2_stats {int dummy; } ;
struct qed_dev {TYPE_1__* ll2; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QED_LEADING_HWFN (struct qed_dev*) ; 
 int qed_ll2_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_ll2_stats*) ; 

__attribute__((used)) static int qed_ll2_stats(struct qed_dev *cdev, struct qed_ll2_stats *stats)
{
	if (!cdev->ll2)
		return -EINVAL;

	return qed_ll2_get_stats(QED_LEADING_HWFN(cdev),
				 cdev->ll2->handle, stats);
}
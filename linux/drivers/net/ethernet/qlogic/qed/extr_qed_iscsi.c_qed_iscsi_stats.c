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
struct qed_iscsi_stats {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int qed_iscsi_get_stats (int /*<<< orphan*/ ,struct qed_iscsi_stats*) ; 

__attribute__((used)) static int qed_iscsi_stats(struct qed_dev *cdev, struct qed_iscsi_stats *stats)
{
	return qed_iscsi_get_stats(QED_AFFIN_HWFN(cdev), stats);
}
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
struct qmp {scalar_t__ msgram; } ;

/* Variables and functions */
 scalar_t__ QMP_DESC_MCORE_CH_STATE ; 
 scalar_t__ QMP_DESC_MCORE_LINK_STATE ; 
 int /*<<< orphan*/  QMP_STATE_DOWN ; 
 int /*<<< orphan*/  qmp_kick (struct qmp*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qmp_close(struct qmp *qmp)
{
	writel(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_CH_STATE);
	writel(QMP_STATE_DOWN, qmp->msgram + QMP_DESC_MCORE_LINK_STATE);
	qmp_kick(qmp);
}
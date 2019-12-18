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
struct qed_hwfn {TYPE_1__* p_l2_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_IS_L2_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void qed_l2_setup(struct qed_hwfn *p_hwfn)
{
	if (!QED_IS_L2_PERSONALITY(p_hwfn))
		return;

	mutex_init(&p_hwfn->p_l2_info->lock);
}
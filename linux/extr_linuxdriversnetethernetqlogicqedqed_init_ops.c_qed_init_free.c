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
struct TYPE_2__ {int /*<<< orphan*/ * b_valid; int /*<<< orphan*/ * init_val; } ;
struct qed_hwfn {TYPE_1__ rt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void qed_init_free(struct qed_hwfn *p_hwfn)
{
	kfree(p_hwfn->rt_data.init_val);
	p_hwfn->rt_data.init_val = NULL;
	kfree(p_hwfn->rt_data.b_valid);
	p_hwfn->rt_data.b_valid = NULL;
}
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
struct dev_pm_opp {TYPE_1__* opp_table; int /*<<< orphan*/  kref; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _opp_kref_release_locked ; 
 int /*<<< orphan*/  kref_put_mutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dev_pm_opp_put(struct dev_pm_opp *opp)
{
	kref_put_mutex(&opp->kref, _opp_kref_release_locked,
		       &opp->opp_table->lock);
}
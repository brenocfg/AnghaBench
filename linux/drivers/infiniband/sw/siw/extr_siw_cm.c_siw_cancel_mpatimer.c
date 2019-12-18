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
struct siw_cep {int /*<<< orphan*/  lock; TYPE_1__* mpa_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_cancel_mpatimer(struct siw_cep *cep)
{
	spin_lock_bh(&cep->lock);
	if (cep->mpa_timer) {
		if (cancel_delayed_work(&cep->mpa_timer->work)) {
			siw_cep_put(cep);
			kfree(cep->mpa_timer); /* not needed again */
		}
		cep->mpa_timer = NULL;
	}
	spin_unlock_bh(&cep->lock);
}
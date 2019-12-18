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
struct ice_pf {int /*<<< orphan*/ * avail_rxqs; int /*<<< orphan*/ * avail_txqs; int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  sw_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_service_task_stop (struct ice_pf*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_deinit_pf(struct ice_pf *pf)
{
	ice_service_task_stop(pf);
	mutex_destroy(&pf->sw_mutex);
	mutex_destroy(&pf->avail_q_mutex);

	if (pf->avail_txqs) {
		bitmap_free(pf->avail_txqs);
		pf->avail_txqs = NULL;
	}

	if (pf->avail_rxqs) {
		bitmap_free(pf->avail_rxqs);
		pf->avail_rxqs = NULL;
	}
}
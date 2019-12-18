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
struct ice_pf {int /*<<< orphan*/ * avail_txqs; TYPE_1__* pdev; void* avail_rxqs; int /*<<< orphan*/  max_pf_rxqs; int /*<<< orphan*/  max_pf_txqs; int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  serv_task; int /*<<< orphan*/  serv_tmr_period; int /*<<< orphan*/  serv_tmr; int /*<<< orphan*/  sw_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ICE_SERVICE_SCHED ; 
 void* bitmap_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_service_task ; 
 int /*<<< orphan*/  ice_service_timer ; 
 int /*<<< orphan*/  ice_set_pf_caps (struct ice_pf*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_init_pf(struct ice_pf *pf)
{
	ice_set_pf_caps(pf);

	mutex_init(&pf->sw_mutex);

	/* setup service timer and periodic service task */
	timer_setup(&pf->serv_tmr, ice_service_timer, 0);
	pf->serv_tmr_period = HZ;
	INIT_WORK(&pf->serv_task, ice_service_task);
	clear_bit(__ICE_SERVICE_SCHED, pf->state);

	mutex_init(&pf->avail_q_mutex);
	pf->avail_txqs = bitmap_zalloc(pf->max_pf_txqs, GFP_KERNEL);
	if (!pf->avail_txqs)
		return -ENOMEM;

	pf->avail_rxqs = bitmap_zalloc(pf->max_pf_rxqs, GFP_KERNEL);
	if (!pf->avail_rxqs) {
		devm_kfree(&pf->pdev->dev, pf->avail_txqs);
		pf->avail_txqs = NULL;
		return -ENOMEM;
	}

	return 0;
}
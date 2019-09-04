#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rss_table_size; } ;
struct TYPE_5__ {TYPE_1__ common_cap; } ;
struct TYPE_6__ {TYPE_2__ func_caps; } ;
struct ice_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  serv_task; int /*<<< orphan*/  serv_tmr_period; int /*<<< orphan*/  serv_tmr; int /*<<< orphan*/  flags; TYPE_3__ hw; int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  avail_rxqs; int /*<<< orphan*/  avail_txqs; int /*<<< orphan*/  sw_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
 int /*<<< orphan*/  ICE_MAX_RXQS ; 
 int /*<<< orphan*/  ICE_MAX_TXQS ; 
 int /*<<< orphan*/  ICE_PF_FLAGS_NBITS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ICE_SERVICE_SCHED ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_service_task ; 
 int /*<<< orphan*/  ice_service_timer ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_init_pf(struct ice_pf *pf)
{
	bitmap_zero(pf->flags, ICE_PF_FLAGS_NBITS);
	set_bit(ICE_FLAG_MSIX_ENA, pf->flags);

	mutex_init(&pf->sw_mutex);
	mutex_init(&pf->avail_q_mutex);

	/* Clear avail_[t|r]x_qs bitmaps (set all to avail) */
	mutex_lock(&pf->avail_q_mutex);
	bitmap_zero(pf->avail_txqs, ICE_MAX_TXQS);
	bitmap_zero(pf->avail_rxqs, ICE_MAX_RXQS);
	mutex_unlock(&pf->avail_q_mutex);

	if (pf->hw.func_caps.common_cap.rss_table_size)
		set_bit(ICE_FLAG_RSS_ENA, pf->flags);

	/* setup service timer and periodic service task */
	timer_setup(&pf->serv_tmr, ice_service_timer, 0);
	pf->serv_tmr_period = HZ;
	INIT_WORK(&pf->serv_task, ice_service_task);
	clear_bit(__ICE_SERVICE_SCHED, pf->state);
}
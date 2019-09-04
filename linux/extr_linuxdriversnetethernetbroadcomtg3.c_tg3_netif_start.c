#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tg3 {TYPE_2__* napi; int /*<<< orphan*/  dev; scalar_t__ link_up; } ;
struct TYPE_4__ {TYPE_1__* hw_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_STATUS_UPDATED ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_enable_ints (struct tg3*) ; 
 int /*<<< orphan*/  tg3_napi_enable (struct tg3*) ; 
 int /*<<< orphan*/  tg3_ptp_resume (struct tg3*) ; 

__attribute__((used)) static inline void tg3_netif_start(struct tg3 *tp)
{
	tg3_ptp_resume(tp);

	/* NOTE: unconditional netif_tx_wake_all_queues is only
	 * appropriate so long as all callers are assured to
	 * have free tx slots (such as after tg3_init_hw)
	 */
	netif_tx_wake_all_queues(tp->dev);

	if (tp->link_up)
		netif_carrier_on(tp->dev);

	tg3_napi_enable(tp);
	tp->napi[0].hw_status->status |= SD_STATUS_UPDATED;
	tg3_enable_ints(tp);
}
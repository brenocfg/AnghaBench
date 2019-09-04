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
struct xgbe_prv_data {unsigned int* prio2q_map; TYPE_2__* pfc; TYPE_1__* ets; } ;
struct TYPE_4__ {int pfc_en; } ;
struct TYPE_3__ {unsigned int* prio_tc; } ;

/* Variables and functions */
 unsigned int IEEE_8021QAZ_MAX_TCS ; 

__attribute__((used)) static bool xgbe_is_pfc_queue(struct xgbe_prv_data *pdata,
			      unsigned int queue)
{
	unsigned int prio, tc;

	for (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++) {
		/* Does this queue handle the priority? */
		if (pdata->prio2q_map[prio] != queue)
			continue;

		/* Get the Traffic Class for this priority */
		tc = pdata->ets->prio_tc[prio];

		/* Check if PFC is enabled for this traffic class */
		if (pdata->pfc->pfc_en & (1 << tc))
			return true;
	}

	return false;
}
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
struct TYPE_4__ {int /*<<< orphan*/  poll; } ;
struct sge_qset {TYPE_2__ napi; int /*<<< orphan*/  netdev; scalar_t__ adap; } ;
struct TYPE_3__ {struct sge_qset* qs; } ;
struct adapter {int /*<<< orphan*/  flags; TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_INIT ; 
 int SGE_QSETS ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_napi(struct adapter *adap)
{
	int i;

	for (i = 0; i < SGE_QSETS; i++) {
		struct sge_qset *qs = &adap->sge.qs[i];

		if (qs->adap)
			netif_napi_add(qs->netdev, &qs->napi, qs->napi.poll,
				       64);
	}

	/*
	 * netif_napi_add() can be called only once per napi_struct because it
	 * adds each new napi_struct to a list.  Be careful not to call it a
	 * second time, e.g., during EEH recovery, by making a note of it.
	 */
	adap->flags |= NAPI_INIT;
}
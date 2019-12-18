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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {TYPE_1__* txcredit_alloc; } ;
struct htc_target {TYPE_2__ pipe; } ;
struct TYPE_3__ {scalar_t__ service_id; scalar_t__ credit_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int ENDPOINT_MAX ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static u8 htc_get_credit_alloc(struct htc_target *target, u16 service_id)
{
	u8 allocation = 0;
	int i;

	for (i = 0; i < ENDPOINT_MAX; i++) {
		if (target->pipe.txcredit_alloc[i].service_id == service_id)
			allocation =
				target->pipe.txcredit_alloc[i].credit_alloc;
	}

	if (allocation == 0) {
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "HTC Service TX : 0x%2.2X : allocation is zero!\n",
			   service_id);
	}

	return allocation;
}
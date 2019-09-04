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
struct TYPE_3__ {scalar_t__ aggregation_timeout; } ;
struct cfhsi {TYPE_2__* qhead; TYPE_1__ cfg; } ;
struct TYPE_4__ {scalar_t__ qlen; } ;

/* Variables and functions */
 scalar_t__ CFHSI_MAX_PKTS ; 
 int CFHSI_PRIO_BEBK ; 

__attribute__((used)) static bool cfhsi_can_send_aggregate(struct cfhsi *cfhsi)
{
	int i;

	if (cfhsi->cfg.aggregation_timeout == 0)
		return true;

	for (i = 0; i < CFHSI_PRIO_BEBK; ++i) {
		if (cfhsi->qhead[i].qlen)
			return true;
	}

	/* TODO: Use aggregation_len instead */
	if (cfhsi->qhead[CFHSI_PRIO_BEBK].qlen >= CFHSI_MAX_PKTS)
		return true;

	return false;
}
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
typedef  scalar_t__ u8 ;
struct ispstat {scalar_t__ state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct ispstat*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ISPSTAT_DISABLED ; 
 scalar_t__ ISPSTAT_DISABLING ; 
 scalar_t__ ISPSTAT_ENABLED ; 
 scalar_t__ ISPSTAT_ENABLING ; 
 int /*<<< orphan*/  stub1 (struct ispstat*,scalar_t__) ; 

__attribute__((used)) static void isp_stat_pcr_enable(struct ispstat *stat, u8 pcr_enable)
{
	if ((stat->state != ISPSTAT_ENABLING &&
	     stat->state != ISPSTAT_ENABLED) && pcr_enable)
		/* Userspace has disabled the module. Aborting. */
		return;

	stat->ops->enable(stat, pcr_enable);
	if (stat->state == ISPSTAT_DISABLING && !pcr_enable)
		stat->state = ISPSTAT_DISABLED;
	else if (stat->state == ISPSTAT_ENABLING && pcr_enable)
		stat->state = ISPSTAT_ENABLED;
}
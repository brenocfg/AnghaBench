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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ counter; } ;
struct qib_pportdata {TYPE_1__ cong_stats; int /*<<< orphan*/  ibport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PMA_PORT_XMIT_WAIT ; 
 scalar_t__ get_counter (int /*<<< orphan*/ *,struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 xmit_wait_get_value_delta(struct qib_pportdata *ppd)
{
	u32 delta;

	delta = get_counter(&ppd->ibport_data, ppd,
			    IB_PMA_PORT_XMIT_WAIT);
	return ppd->cong_stats.counter + delta;
}
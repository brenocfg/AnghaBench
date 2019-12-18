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
typedef  unsigned int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  syncpt; } ;
struct host1x_cdma {TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_syncpt_incr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_load (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdma_timeout_cpu_incr(struct host1x_cdma *cdma, u32 getptr,
				u32 syncpt_incrs, u32 syncval, u32 nr_slots)
{
	unsigned int i;

	for (i = 0; i < syncpt_incrs; i++)
		host1x_syncpt_incr(cdma->timeout.syncpt);

	/* after CPU incr, ensure shadow is up to date */
	host1x_syncpt_load(cdma->timeout.syncpt);
}
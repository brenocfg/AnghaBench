#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cfq_queue {int dummy; } ;
typedef  enum wl_type_t { ____Placeholder_wl_type_t } wl_type_t ;

/* Variables and functions */
 int ASYNC_WORKLOAD ; 
 int SYNC_NOIDLE_WORKLOAD ; 
 int SYNC_WORKLOAD ; 
 int /*<<< orphan*/  cfq_cfqq_idle_window (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_cfqq_sync (struct cfq_queue*) ; 

__attribute__((used)) static enum wl_type_t cfqq_type(struct cfq_queue *cfqq)
{
	if (!cfq_cfqq_sync(cfqq))
		return ASYNC_WORKLOAD;
	if (!cfq_cfqq_idle_window(cfqq))
		return SYNC_NOIDLE_WORKLOAD;
	return SYNC_WORKLOAD;
}
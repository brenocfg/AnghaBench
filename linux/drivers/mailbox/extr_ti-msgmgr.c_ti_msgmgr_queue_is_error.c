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
typedef  int u32 ;
struct ti_queue_inst {int /*<<< orphan*/  queue_state; } ;
struct ti_msgmgr_desc {int status_err_mask; int /*<<< orphan*/  is_sproxy; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ti_msgmgr_queue_is_error(const struct ti_msgmgr_desc *d,
					    struct ti_queue_inst *qinst)
{
	u32 val;

	/* Msgmgr has no error detection */
	if (!d->is_sproxy)
		return false;

	/*
	 * We cannot use relaxed operation here - update may happen
	 * real-time.
	 */
	val = readl(qinst->queue_state) & d->status_err_mask;

	return val ? true : false;
}
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
struct ti_msgmgr_desc {int status_cnt_mask; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ti_msgmgr_queue_get_num_messages(const struct ti_msgmgr_desc *d,
				 struct ti_queue_inst *qinst)
{
	u32 val;
	u32 status_cnt_mask = d->status_cnt_mask;

	/*
	 * We cannot use relaxed operation here - update may happen
	 * real-time.
	 */
	val = readl(qinst->queue_state) & status_cnt_mask;
	val >>= __ffs(status_cnt_mask);

	return val;
}
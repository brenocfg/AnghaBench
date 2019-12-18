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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  max_entries_in_tx_burst; } ;
struct ena_com_io_sq {int /*<<< orphan*/  entries_in_tx_burst_left; int /*<<< orphan*/  qid; int /*<<< orphan*/  db_addr; int /*<<< orphan*/  tail; TYPE_1__ llq_info; } ;

/* Variables and functions */
 scalar_t__ is_llq_max_tx_burst_exists (struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ena_com_write_sq_doorbell(struct ena_com_io_sq *io_sq)
{
	u16 max_entries_in_tx_burst = io_sq->llq_info.max_entries_in_tx_burst;
	u16 tail = io_sq->tail;

	pr_debug("write submission queue doorbell for queue: %d tail: %d\n",
		 io_sq->qid, tail);

	writel(tail, io_sq->db_addr);

	if (is_llq_max_tx_burst_exists(io_sq)) {
		pr_debug("reset available entries in tx burst for queue %d to %d\n",
			 io_sq->qid, max_entries_in_tx_burst);
		io_sq->entries_in_tx_burst_left = max_entries_in_tx_burst;
	}

	return 0;
}
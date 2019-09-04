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
typedef  int /*<<< orphan*/  u16 ;
struct ena_com_io_sq {int /*<<< orphan*/  db_addr; int /*<<< orphan*/  qid; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ena_com_write_sq_doorbell(struct ena_com_io_sq *io_sq)
{
	u16 tail;

	tail = io_sq->tail;

	pr_debug("write submission queue doorbell for queue: %d tail: %d\n",
		 io_sq->qid, tail);

	writel(tail, io_sq->db_addr);

	return 0;
}
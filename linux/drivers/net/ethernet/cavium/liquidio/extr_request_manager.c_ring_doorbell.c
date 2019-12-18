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
struct octeon_instr_queue {int /*<<< orphan*/  last_db_time; scalar_t__ fill_cnt; int /*<<< orphan*/  doorbell_reg; } ;
struct octeon_device {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ OCT_DEV_RUNNING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ring_doorbell(struct octeon_device *oct, struct octeon_instr_queue *iq)
{
	if (atomic_read(&oct->status) == OCT_DEV_RUNNING) {
		writel(iq->fill_cnt, iq->doorbell_reg);
		/* make sure doorbell write goes through */
		iq->fill_cnt = 0;
		iq->last_db_time = jiffies;
		return;
	}
}
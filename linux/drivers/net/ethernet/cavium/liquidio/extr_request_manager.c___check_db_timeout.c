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
typedef  size_t u64 ;
struct octeon_instr_queue {size_t last_db_time; size_t db_timeout; int /*<<< orphan*/  instr_pending; } ;
struct octeon_device {struct octeon_instr_queue** instr_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 size_t jiffies ; 
 int /*<<< orphan*/  lio_enable_irq (int /*<<< orphan*/ *,struct octeon_instr_queue*) ; 
 int /*<<< orphan*/  octeon_flush_iq (struct octeon_device*,struct octeon_instr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (size_t,unsigned long) ; 

__attribute__((used)) static void __check_db_timeout(struct octeon_device *oct, u64 iq_no)
{
	struct octeon_instr_queue *iq;
	u64 next_time;

	if (!oct)
		return;

	iq = oct->instr_queue[iq_no];
	if (!iq)
		return;

	/* return immediately, if no work pending */
	if (!atomic_read(&iq->instr_pending))
		return;
	/* If jiffies - last_db_time < db_timeout do nothing  */
	next_time = iq->last_db_time + iq->db_timeout;
	if (!time_after(jiffies, (unsigned long)next_time))
		return;
	iq->last_db_time = jiffies;

	/* Flush the instruction queue */
	octeon_flush_iq(oct, iq, 0);

	lio_enable_irq(NULL, iq);
}
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
typedef  size_t u32 ;
struct octeon_instr_queue {scalar_t__ fill_cnt; int /*<<< orphan*/  post_lock; scalar_t__ allow_soft_cmds; } ;
struct octeon_device {struct octeon_instr_queue** instr_queue; } ;
struct iq_post_status {scalar_t__ status; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  INCR_INSTRQUEUE_PKT_COUNT (struct octeon_device*,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IQ_SEND_FAILED ; 
 scalar_t__ IQ_SEND_STOP ; 
 scalar_t__ MAX_OCTEON_FILL_COUNT ; 
 int /*<<< orphan*/  __add_to_request_list (struct octeon_instr_queue*,int /*<<< orphan*/ ,void*,size_t) ; 
 struct iq_post_status __post_command2 (struct octeon_instr_queue*,void*) ; 
 int /*<<< orphan*/  bytes_sent ; 
 int /*<<< orphan*/  instr_dropped ; 
 int /*<<< orphan*/  instr_posted ; 
 int octeon_report_sent_bytes_to_bql (void*,size_t) ; 
 int /*<<< orphan*/  ring_doorbell (struct octeon_device*,struct octeon_instr_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int
octeon_send_command(struct octeon_device *oct, u32 iq_no,
		    u32 force_db, void *cmd, void *buf,
		    u32 datasize, u32 reqtype)
{
	int xmit_stopped;
	struct iq_post_status st;
	struct octeon_instr_queue *iq = oct->instr_queue[iq_no];

	/* Get the lock and prevent other tasks and tx interrupt handler from
	 * running.
	 */
	if (iq->allow_soft_cmds)
		spin_lock_bh(&iq->post_lock);

	st = __post_command2(iq, cmd);

	if (st.status != IQ_SEND_FAILED) {
		xmit_stopped = octeon_report_sent_bytes_to_bql(buf, reqtype);
		__add_to_request_list(iq, st.index, buf, reqtype);
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, bytes_sent, datasize);
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_posted, 1);

		if (iq->fill_cnt >= MAX_OCTEON_FILL_COUNT || force_db ||
		    xmit_stopped || st.status == IQ_SEND_STOP)
			ring_doorbell(oct, iq);
	} else {
		INCR_INSTRQUEUE_PKT_COUNT(oct, iq_no, instr_dropped, 1);
	}

	if (iq->allow_soft_cmds)
		spin_unlock_bh(&iq->post_lock);

	/* This is only done here to expedite packets being flushed
	 * for cases where there are no IQ completion interrupts.
	 */

	return st.status;
}
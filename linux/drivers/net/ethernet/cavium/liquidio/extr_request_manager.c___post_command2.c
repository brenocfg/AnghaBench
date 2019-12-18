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
typedef  int /*<<< orphan*/  u8 ;
struct octeon_instr_queue {int max_count; int host_write_index; int /*<<< orphan*/  instr_pending; int /*<<< orphan*/  fill_cnt; } ;
struct iq_post_status {int index; int /*<<< orphan*/  status; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IQ_SEND_FAILED ; 
 int /*<<< orphan*/  IQ_SEND_OK ; 
 int /*<<< orphan*/  IQ_SEND_STOP ; 
 int /*<<< orphan*/  __copy_cmd_into_iq (struct octeon_instr_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int incr_index (int,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline struct iq_post_status
__post_command2(struct octeon_instr_queue *iq, u8 *cmd)
{
	struct iq_post_status st;

	st.status = IQ_SEND_OK;

	/* This ensures that the read index does not wrap around to the same
	 * position if queue gets full before Octeon could fetch any instr.
	 */
	if (atomic_read(&iq->instr_pending) >= (s32)(iq->max_count - 1)) {
		st.status = IQ_SEND_FAILED;
		st.index = -1;
		return st;
	}

	if (atomic_read(&iq->instr_pending) >= (s32)(iq->max_count - 2))
		st.status = IQ_SEND_STOP;

	__copy_cmd_into_iq(iq, cmd);

	/* "index" is returned, host_write_index is modified. */
	st.index = iq->host_write_index;
	iq->host_write_index = incr_index(iq->host_write_index, 1,
					  iq->max_count);
	iq->fill_cnt++;

	/* Flush the command into memory. We need to be sure the data is in
	 * memory before indicating that the instruction is pending.
	 */
	wmb();

	atomic_inc(&iq->instr_pending);

	return st;
}
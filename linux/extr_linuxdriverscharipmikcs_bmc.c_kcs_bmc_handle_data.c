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
typedef  void* u8 ;
struct kcs_bmc {int phase; int data_in_avail; void* error; int /*<<< orphan*/  data_out_idx; void** data_out; int /*<<< orphan*/  data_out_len; int /*<<< orphan*/  queue; int /*<<< orphan*/  data_in_idx; void** data_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_STATE ; 
 int /*<<< orphan*/  IDLE_STATE ; 
 void* KCS_CMD_READ_BYTE ; 
 void* KCS_LENGTH_ERROR ; 
 int /*<<< orphan*/  KCS_MSG_BUFSIZ ; 
#define  KCS_PHASE_ABORT_ERROR1 133 
#define  KCS_PHASE_ABORT_ERROR2 132 
 void* KCS_PHASE_IDLE ; 
#define  KCS_PHASE_READ 131 
#define  KCS_PHASE_WRITE_DATA 130 
 int KCS_PHASE_WRITE_DONE ; 
#define  KCS_PHASE_WRITE_END_CMD 129 
#define  KCS_PHASE_WRITE_START 128 
 void* KCS_ZERO_DATA ; 
 int /*<<< orphan*/  READ_STATE ; 
 int /*<<< orphan*/  WRITE_STATE ; 
 int /*<<< orphan*/  kcs_force_abort (struct kcs_bmc*) ; 
 void* read_data (struct kcs_bmc*) ; 
 int /*<<< orphan*/  set_state (struct kcs_bmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_data (struct kcs_bmc*,void*) ; 

__attribute__((used)) static void kcs_bmc_handle_data(struct kcs_bmc *kcs_bmc)
{
	u8 data;

	switch (kcs_bmc->phase) {
	case KCS_PHASE_WRITE_START:
		kcs_bmc->phase = KCS_PHASE_WRITE_DATA;
		/* fall through */

	case KCS_PHASE_WRITE_DATA:
		if (kcs_bmc->data_in_idx < KCS_MSG_BUFSIZ) {
			set_state(kcs_bmc, WRITE_STATE);
			write_data(kcs_bmc, KCS_ZERO_DATA);
			kcs_bmc->data_in[kcs_bmc->data_in_idx++] =
						read_data(kcs_bmc);
		} else {
			kcs_force_abort(kcs_bmc);
			kcs_bmc->error = KCS_LENGTH_ERROR;
		}
		break;

	case KCS_PHASE_WRITE_END_CMD:
		if (kcs_bmc->data_in_idx < KCS_MSG_BUFSIZ) {
			set_state(kcs_bmc, READ_STATE);
			kcs_bmc->data_in[kcs_bmc->data_in_idx++] =
						read_data(kcs_bmc);
			kcs_bmc->phase = KCS_PHASE_WRITE_DONE;
			kcs_bmc->data_in_avail = true;
			wake_up_interruptible(&kcs_bmc->queue);
		} else {
			kcs_force_abort(kcs_bmc);
			kcs_bmc->error = KCS_LENGTH_ERROR;
		}
		break;

	case KCS_PHASE_READ:
		if (kcs_bmc->data_out_idx == kcs_bmc->data_out_len)
			set_state(kcs_bmc, IDLE_STATE);

		data = read_data(kcs_bmc);
		if (data != KCS_CMD_READ_BYTE) {
			set_state(kcs_bmc, ERROR_STATE);
			write_data(kcs_bmc, KCS_ZERO_DATA);
			break;
		}

		if (kcs_bmc->data_out_idx == kcs_bmc->data_out_len) {
			write_data(kcs_bmc, KCS_ZERO_DATA);
			kcs_bmc->phase = KCS_PHASE_IDLE;
			break;
		}

		write_data(kcs_bmc,
			kcs_bmc->data_out[kcs_bmc->data_out_idx++]);
		break;

	case KCS_PHASE_ABORT_ERROR1:
		set_state(kcs_bmc, READ_STATE);
		read_data(kcs_bmc);
		write_data(kcs_bmc, kcs_bmc->error);
		kcs_bmc->phase = KCS_PHASE_ABORT_ERROR2;
		break;

	case KCS_PHASE_ABORT_ERROR2:
		set_state(kcs_bmc, IDLE_STATE);
		read_data(kcs_bmc);
		write_data(kcs_bmc, KCS_ZERO_DATA);
		kcs_bmc->phase = KCS_PHASE_IDLE;
		break;

	default:
		kcs_force_abort(kcs_bmc);
		break;
	}
}
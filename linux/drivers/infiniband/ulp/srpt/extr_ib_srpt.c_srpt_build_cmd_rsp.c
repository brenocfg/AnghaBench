#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int scsi_sense_length; } ;
struct TYPE_3__ {struct srp_rsp* buf; } ;
struct srpt_send_ioctx {TYPE_2__ cmd; int /*<<< orphan*/ * sense_data; TYPE_1__ ioctx; } ;
struct srpt_rdma_ch {int max_ti_iu_len; int /*<<< orphan*/  req_lim_delta; } ;
struct srp_rsp {int status; void* sense_data_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  tag; void* req_lim_delta; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int MIN_MAX_RSP_SIZE ; 
 int /*<<< orphan*/  SRP_RSP ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_SNSVALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (struct srp_rsp*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct srp_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static int srpt_build_cmd_rsp(struct srpt_rdma_ch *ch,
			      struct srpt_send_ioctx *ioctx, u64 tag,
			      int status)
{
	struct srp_rsp *srp_rsp;
	const u8 *sense_data;
	int sense_data_len, max_sense_len;

	/*
	 * The lowest bit of all SAM-3 status codes is zero (see also
	 * paragraph 5.3 in SAM-3).
	 */
	WARN_ON(status & 1);

	srp_rsp = ioctx->ioctx.buf;
	BUG_ON(!srp_rsp);

	sense_data = ioctx->sense_data;
	sense_data_len = ioctx->cmd.scsi_sense_length;
	WARN_ON(sense_data_len > sizeof(ioctx->sense_data));

	memset(srp_rsp, 0, sizeof(*srp_rsp));
	srp_rsp->opcode = SRP_RSP;
	srp_rsp->req_lim_delta =
		cpu_to_be32(1 + atomic_xchg(&ch->req_lim_delta, 0));
	srp_rsp->tag = tag;
	srp_rsp->status = status;

	if (sense_data_len) {
		BUILD_BUG_ON(MIN_MAX_RSP_SIZE <= sizeof(*srp_rsp));
		max_sense_len = ch->max_ti_iu_len - sizeof(*srp_rsp);
		if (sense_data_len > max_sense_len) {
			pr_warn("truncated sense data from %d to %d bytes\n",
				sense_data_len, max_sense_len);
			sense_data_len = max_sense_len;
		}

		srp_rsp->flags |= SRP_RSP_FLAG_SNSVALID;
		srp_rsp->sense_data_len = cpu_to_be32(sense_data_len);
		memcpy(srp_rsp + 1, sense_data, sense_data_len);
	}

	return sizeof(*srp_rsp) + sense_data_len;
}
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
struct TYPE_2__ {unsigned int residual_count; } ;
struct vscsibk_pend {unsigned char* sense_buffer; int result; TYPE_1__ se_cmd; struct vscsibk_info* info; } ;
struct vscsibk_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ log_print_stat ; 
 int /*<<< orphan*/  scsiback_do_resp_with_sense (unsigned char*,int,unsigned int,struct vscsibk_pend*) ; 
 int /*<<< orphan*/  scsiback_fast_flush_area (struct vscsibk_pend*) ; 
 int /*<<< orphan*/  scsiback_print_status (unsigned char*,int,struct vscsibk_pend*) ; 
 int /*<<< orphan*/  scsiback_put (struct vscsibk_info*) ; 
 int /*<<< orphan*/  target_put_sess_cmd (TYPE_1__*) ; 

__attribute__((used)) static void scsiback_cmd_done(struct vscsibk_pend *pending_req)
{
	struct vscsibk_info *info = pending_req->info;
	unsigned char *sense_buffer;
	unsigned int resid;
	int errors;

	sense_buffer = pending_req->sense_buffer;
	resid        = pending_req->se_cmd.residual_count;
	errors       = pending_req->result;

	if (errors && log_print_stat)
		scsiback_print_status(sense_buffer, errors, pending_req);

	scsiback_fast_flush_area(pending_req);
	scsiback_do_resp_with_sense(sense_buffer, errors, resid, pending_req);
	scsiback_put(info);
	/*
	 * Drop the extra KREF_ACK reference taken by target_submit_cmd_map_sgls()
	 * ahead of scsiback_check_stop_free() ->  transport_generic_free_cmd()
	 * final se_cmd->cmd_kref put.
	 */
	target_put_sess_cmd(&pending_req->se_cmd);
}
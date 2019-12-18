#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_sg_context {scalar_t__ length; scalar_t__ cur_offset; } ;
struct esas2r_request {int /*<<< orphan*/  req_stat; TYPE_3__* vrq; int /*<<< orphan*/  interrupt_cb; scalar_t__ interrupt_cx; } ;
struct esas2r_flash_context {scalar_t__ func; scalar_t__ curr_len; int /*<<< orphan*/  flsh_addr; struct esas2r_sg_context sgc; int /*<<< orphan*/  interrupt_cb; } ;
struct esas2r_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sge; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_BUSY ; 
 scalar_t__ VDA_FLASH_BEGINW ; 
 int /*<<< orphan*/  esas2r_build_flash_req (struct esas2r_adapter*,struct esas2r_request*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_build_sg_list (struct esas2r_adapter*,struct esas2r_request*,struct esas2r_sg_context*) ; 
 int /*<<< orphan*/  esas2r_calc_byte_xor_cksum (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_fmapi_callback ; 
 int /*<<< orphan*/  esas2r_rq_free_sg_lists (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_sgc_init (struct esas2r_sg_context*,struct esas2r_adapter*,struct esas2r_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void build_flash_msg(struct esas2r_adapter *a,
			    struct esas2r_request *rq)
{
	struct esas2r_flash_context *fc =
		(struct esas2r_flash_context *)rq->interrupt_cx;
	struct esas2r_sg_context *sgc = &fc->sgc;
	u8 cksum = 0;

	/* calculate the checksum */
	if (fc->func == VDA_FLASH_BEGINW) {
		if (sgc->cur_offset)
			cksum = esas2r_calc_byte_xor_cksum(sgc->cur_offset,
							   sgc->length,
							   0);
		rq->interrupt_cb = esas2r_fmapi_callback;
	} else {
		rq->interrupt_cb = fc->interrupt_cb;
	}
	esas2r_build_flash_req(a,
			       rq,
			       fc->func,
			       cksum,
			       fc->flsh_addr,
			       sgc->length);

	esas2r_rq_free_sg_lists(rq, a);

	/*
	 * remember the length we asked for.  we have to keep track of
	 * the current amount done so we know how much to compare when
	 * doing the verification phase.
	 */
	fc->curr_len = fc->sgc.length;

	if (sgc->cur_offset) {
		/* setup the S/G context to build the S/G table  */
		esas2r_sgc_init(sgc, a, rq, &rq->vrq->flash.data.sge[0]);

		if (!esas2r_build_sg_list(a, rq, sgc)) {
			rq->req_stat = RS_BUSY;
			return;
		}
	} else {
		fc->sgc.length = 0;
	}

	/* update the flsh_addr to the next one to write to  */
	fc->flsh_addr += fc->curr_len;
}
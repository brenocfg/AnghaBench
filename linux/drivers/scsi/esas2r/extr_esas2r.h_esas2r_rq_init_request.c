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
struct TYPE_5__ {int handle; int /*<<< orphan*/  ppsense_buf; scalar_t__ reserved; scalar_t__ flags; scalar_t__ chain_offset; scalar_t__ sg_list_offset; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  function; } ;
union atto_vda_req {TYPE_2__ scsi; } ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__* dwords; } ;
struct esas2r_request {TYPE_3__* vrq_md; int /*<<< orphan*/  vda_req_sz; TYPE_1__ func_rsp; int /*<<< orphan*/  req_type; int /*<<< orphan*/  req_stat; scalar_t__ timeout; scalar_t__ flags; int /*<<< orphan*/  comp_cb; int /*<<< orphan*/ * interrupt_cb; void* data_buf; int /*<<< orphan*/  sg_table_head; union atto_vda_req* vrq; } ;
struct esas2r_adapter {int /*<<< orphan*/  cmd_ref_no; struct esas2r_request** req_table; } ;
struct TYPE_6__ {scalar_t__ phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t LOWORD (int) ; 
 int /*<<< orphan*/  RQ_SIZE_DEFAULT ; 
 int /*<<< orphan*/  RS_PENDING ; 
 int /*<<< orphan*/  RT_INI_REQ ; 
 int /*<<< orphan*/  SENSE_DATA_SZ ; 
 int /*<<< orphan*/  VDA_FUNC_SCSI ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  esas2r_bugon () ; 
 int /*<<< orphan*/  esas2r_complete_request_cb ; 

__attribute__((used)) static inline void esas2r_rq_init_request(struct esas2r_request *rq,
					  struct esas2r_adapter *a)
{
	union atto_vda_req *vrq = rq->vrq;

	INIT_LIST_HEAD(&rq->sg_table_head);
	rq->data_buf = (void *)(vrq + 1);
	rq->interrupt_cb = NULL;
	rq->comp_cb = esas2r_complete_request_cb;
	rq->flags = 0;
	rq->timeout = 0;
	rq->req_stat = RS_PENDING;
	rq->req_type = RT_INI_REQ;

	/* clear the outbound response */
	rq->func_rsp.dwords[0] = 0;
	rq->func_rsp.dwords[1] = 0;

	/*
	 * clear the size of the VDA request.  esas2r_build_sg_list() will
	 * only allow the size of the request to grow.  there are some
	 * management requests that go through there twice and the second
	 * time through sets a smaller request size.  if this is not modified
	 * at all we'll set it to the size of the entire VDA request.
	 */
	rq->vda_req_sz = RQ_SIZE_DEFAULT;

	/* req_table entry should be NULL at this point - if not, halt */

	if (a->req_table[LOWORD(vrq->scsi.handle)])
		esas2r_bugon();

	/* fill in the table for this handle so we can get back to the
	 * request.
	 */
	a->req_table[LOWORD(vrq->scsi.handle)] = rq;

	/*
	 * add a reference number to the handle to make it unique (until it
	 * wraps of course) while preserving the least significant word
	 */
	vrq->scsi.handle = (a->cmd_ref_no++ << 16) | (u16)vrq->scsi.handle;

	/*
	 * the following formats a SCSI request.  the caller can override as
	 * necessary.  clear_vda_request can be called to clear the VDA
	 * request for another type of request.
	 */
	vrq->scsi.function = VDA_FUNC_SCSI;
	vrq->scsi.sense_len = SENSE_DATA_SZ;

	/* clear out sg_list_offset and chain_offset */
	vrq->scsi.sg_list_offset = 0;
	vrq->scsi.chain_offset = 0;
	vrq->scsi.flags = 0;
	vrq->scsi.reserved = 0;

	/* set the sense buffer to be the data payload buffer */
	vrq->scsi.ppsense_buf
		= cpu_to_le64(rq->vrq_md->phys_addr +
			      sizeof(union atto_vda_req));
}
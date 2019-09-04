#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct srp_request {int /*<<< orphan*/  scmnd; TYPE_4__* indirect_desc; struct srp_fr_desc** fr_list; } ;
struct srp_rdma_ch {TYPE_2__* target; } ;
struct srp_map_state {int ndesc; int nmdesc; } ;
struct srp_fr_desc {TYPE_3__* mr; } ;
struct srp_device {scalar_t__ use_fmr; scalar_t__ use_fast_reg; } ;
struct scatterlist {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_6__ {TYPE_1__* srp_host; } ;
struct TYPE_5__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ scsi_bufflen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_check_mapping(struct srp_map_state *state,
			      struct srp_rdma_ch *ch, struct srp_request *req,
			      struct scatterlist *scat, int count)
{
	struct srp_device *dev = ch->target->srp_host->srp_dev;
	struct srp_fr_desc **pfr;
	u64 desc_len = 0, mr_len = 0;
	int i;

	for (i = 0; i < state->ndesc; i++)
		desc_len += be32_to_cpu(req->indirect_desc[i].len);
	if (dev->use_fast_reg)
		for (i = 0, pfr = req->fr_list; i < state->nmdesc; i++, pfr++)
			mr_len += (*pfr)->mr->length;
	else if (dev->use_fmr)
		for (i = 0; i < state->nmdesc; i++)
			mr_len += be32_to_cpu(req->indirect_desc[i].len);
	if (desc_len != scsi_bufflen(req->scmnd) ||
	    mr_len > scsi_bufflen(req->scmnd))
		pr_err("Inconsistent: scsi len %d <> desc len %lld <> mr len %lld; ndesc %d; nmdesc = %d\n",
		       scsi_bufflen(req->scmnd), desc_len, mr_len,
		       state->ndesc, state->nmdesc);
}
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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct iwarp_rdma_write {int /*<<< orphan*/  sink_to; int /*<<< orphan*/  sink_stag; } ;
struct TYPE_2__ {struct iwarp_rdma_write rwrite; } ;
struct siw_rx_stream {scalar_t__ ddp_stag; scalar_t__ ddp_to; TYPE_1__ hdr; } ;
struct siw_rx_fpdu {scalar_t__ pbl_idx; scalar_t__ first_ddp_seg; } ;
typedef  enum ddp_ecode { ____Placeholder_ddp_ecode } ddp_ecode ;

/* Variables and functions */
 int DDP_ECODE_T_BASE_BOUNDS ; 
 int DDP_ECODE_T_INVALID_STAG ; 
 int /*<<< orphan*/  DDP_ETYPE_TAGGED_BUF ; 
 int EINVAL ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_DDP ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  qp_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_qp (struct siw_rx_stream*) ; 
 int /*<<< orphan*/  siw_init_terminate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int siw_write_check_ntoh(struct siw_rx_stream *srx,
				struct siw_rx_fpdu *frx)
{
	struct iwarp_rdma_write *write = &srx->hdr.rwrite;
	enum ddp_ecode ecode;

	u32 sink_stag = be32_to_cpu(write->sink_stag);
	u64 sink_to = be64_to_cpu(write->sink_to);

	if (frx->first_ddp_seg) {
		srx->ddp_stag = sink_stag;
		srx->ddp_to = sink_to;
		frx->pbl_idx = 0;
	} else {
		if (unlikely(srx->ddp_stag != sink_stag)) {
			pr_warn("siw: [QP %u]: write stag: %08x != %08x\n",
				qp_id(rx_qp(srx)), sink_stag,
				srx->ddp_stag);
			ecode = DDP_ECODE_T_INVALID_STAG;
			goto error;
		}
		if (unlikely(srx->ddp_to != sink_to)) {
			pr_warn("siw: [QP %u]: write off: %016llx != %016llx\n",
				qp_id(rx_qp(srx)),
				(unsigned long long)sink_to,
				(unsigned long long)srx->ddp_to);
			ecode = DDP_ECODE_T_BASE_BOUNDS;
			goto error;
		}
	}
	return 0;
error:
	siw_init_terminate(rx_qp(srx), TERM_ERROR_LAYER_DDP,
			   DDP_ETYPE_TAGGED_BUF, ecode, 0);
	return -EINVAL;
}
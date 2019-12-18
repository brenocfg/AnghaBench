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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct srp_target_port {TYPE_1__* srp_host; } ;
struct srp_request {int indirect_dma_addr; int /*<<< orphan*/  indirect_desc; } ;
struct srp_rdma_ch {struct srp_target_port* target; } ;
struct TYPE_4__ {void** next; void** end; } ;
struct srp_map_state {int base_dma_addr; int* pages; int npages; int /*<<< orphan*/  key; struct scatterlist* sg; int /*<<< orphan*/  dma_len; struct srp_map_state* desc; TYPE_2__ gen; } ;
struct srp_direct_buf {int base_dma_addr; int* pages; int npages; int /*<<< orphan*/  key; struct scatterlist* sg; int /*<<< orphan*/  dma_len; struct srp_direct_buf* desc; TYPE_2__ gen; } ;
struct srp_device {int mr_page_mask; scalar_t__ use_fmr; scalar_t__ use_fast_reg; } ;
struct scatterlist {int dma_address; int /*<<< orphan*/  length; int /*<<< orphan*/  dma_length; } ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  idb_desc ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct srp_device* srp_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (struct srp_map_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int srp_map_finish_fmr (struct srp_map_state*,struct srp_rdma_ch*) ; 
 int srp_map_finish_fr (struct srp_map_state*,struct srp_request*,struct srp_rdma_ch*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int srp_map_idb(struct srp_rdma_ch *ch, struct srp_request *req,
		       void **next_mr, void **end_mr, u32 idb_len,
		       __be32 *idb_rkey)
{
	struct srp_target_port *target = ch->target;
	struct srp_device *dev = target->srp_host->srp_dev;
	struct srp_map_state state;
	struct srp_direct_buf idb_desc;
	u64 idb_pages[1];
	struct scatterlist idb_sg[1];
	int ret;

	memset(&state, 0, sizeof(state));
	memset(&idb_desc, 0, sizeof(idb_desc));
	state.gen.next = next_mr;
	state.gen.end = end_mr;
	state.desc = &idb_desc;
	state.base_dma_addr = req->indirect_dma_addr;
	state.dma_len = idb_len;

	if (dev->use_fast_reg) {
		state.sg = idb_sg;
		sg_init_one(idb_sg, req->indirect_desc, idb_len);
		idb_sg->dma_address = req->indirect_dma_addr; /* hack! */
#ifdef CONFIG_NEED_SG_DMA_LENGTH
		idb_sg->dma_length = idb_sg->length;	      /* hack^2 */
#endif
		ret = srp_map_finish_fr(&state, req, ch, 1, NULL);
		if (ret < 0)
			return ret;
		WARN_ON_ONCE(ret < 1);
	} else if (dev->use_fmr) {
		state.pages = idb_pages;
		state.pages[0] = (req->indirect_dma_addr &
				  dev->mr_page_mask);
		state.npages = 1;
		ret = srp_map_finish_fmr(&state, ch);
		if (ret < 0)
			return ret;
	} else {
		return -EINVAL;
	}

	*idb_rkey = idb_desc.key;

	return 0;
}
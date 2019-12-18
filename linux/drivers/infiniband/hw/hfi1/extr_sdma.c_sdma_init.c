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
typedef  scalar_t__ uint ;
typedef  int u8 ;
typedef  unsigned int u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct sdma_txreq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  comp; int /*<<< orphan*/  kref; } ;
struct sdma_engine {unsigned int this_idx; int descq_cnt; int sdma_shift; int sdma_mask; unsigned int int_mask; unsigned int progress_mask; unsigned int idle_mask; int imask; int ahg_bits; scalar_t__ head_phys; void* head_dma; int /*<<< orphan*/  tx_ring; void* descq; scalar_t__ descq_phys; int /*<<< orphan*/  err_progress_check_timer; scalar_t__ progress_check_head; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  err_halt_worker; int /*<<< orphan*/  sdma_sw_clean_up_task; int /*<<< orphan*/  sdma_hw_clean_up_task; int /*<<< orphan*/  tail_csr; int /*<<< orphan*/  dmawait; int /*<<< orphan*/  flushlist; TYPE_2__ state; int /*<<< orphan*/  waitlock; int /*<<< orphan*/  flushlist_lock; int /*<<< orphan*/  senddmactrl_lock; int /*<<< orphan*/  head_lock; int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  desc_avail; struct hfi1_pportdata* ppd; struct hfi1_devdata* dd; } ;
struct rhashtable {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  vls_operational; } ;
struct hfi1_devdata {size_t sdma_heads_size; size_t num_sdma; struct rhashtable* sdma_rht; int /*<<< orphan*/  flags; scalar_t__ sdma_heads_phys; void* sdma_heads_dma; struct sdma_engine* per_sdma; void* sdma_pad_dma; scalar_t__ sdma_pad_phys; TYPE_1__* pcidev; int /*<<< orphan*/  node; int /*<<< orphan*/  default_desc1; int /*<<< orphan*/  sdma_unfreeze_count; int /*<<< orphan*/  sdma_unfreeze_wq; struct hfi1_pportdata* pport; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFI1_CAP_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFI1_HAS_SDMA_TIMEOUT ; 
 int /*<<< orphan*/  HFI1_HAS_SEND_DMA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t L1_CACHE_BYTES ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA ; 
 int /*<<< orphan*/  SDMA_AHG ; 
 size_t SDMA_BLOCK_SIZE ; 
 int /*<<< orphan*/  SDMA_DESC1_HEAD_TO_HOST_FLAG ; 
 int /*<<< orphan*/  SDMA_DESC1_INT_REQ_FLAG ; 
 scalar_t__ SDMA_DESC_INTR ; 
 int SDMA_PAD ; 
 int /*<<< orphan*/  TAIL ; 
 unsigned int TXE_NUM_SDMA_ENGINES ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t chip_sdma_engines (struct hfi1_devdata*) ; 
 size_t chip_sdma_mem_size (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,size_t,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_kctxt_csr_addr (struct hfi1_devdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_sdma_regs (struct sdma_engine*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct sdma_engine* kcalloc_node (size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rhashtable*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvzalloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rhashtable* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t mod_num_sdma ; 
 scalar_t__ ns_to_cclock (struct hfi1_devdata*,scalar_t__) ; 
 size_t num_vls ; 
 int rhashtable_init (struct rhashtable*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_clean (struct hfi1_devdata*,size_t) ; 
 int /*<<< orphan*/  sdma_descq_freecnt (struct sdma_engine*) ; 
 scalar_t__ sdma_desct_intr ; 
 int /*<<< orphan*/  sdma_err_halt_wait ; 
 int /*<<< orphan*/  sdma_err_progress_check ; 
 int /*<<< orphan*/  sdma_field_flush ; 
 int sdma_get_descq_cnt () ; 
 int /*<<< orphan*/  sdma_hw_clean_up_task ; 
 scalar_t__ sdma_idle_cnt ; 
 int sdma_map_init (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_rht_params ; 
 int /*<<< orphan*/  sdma_set_state (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_state_s00_hw_down ; 
 int /*<<< orphan*/  sdma_sw_clean_up_task ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sdma_init(struct hfi1_devdata *dd, u8 port)
{
	unsigned this_idx;
	struct sdma_engine *sde;
	struct rhashtable *tmp_sdma_rht;
	u16 descq_cnt;
	void *curr_head;
	struct hfi1_pportdata *ppd = dd->pport + port;
	u32 per_sdma_credits;
	uint idle_cnt = sdma_idle_cnt;
	size_t num_engines = chip_sdma_engines(dd);
	int ret = -ENOMEM;

	if (!HFI1_CAP_IS_KSET(SDMA)) {
		HFI1_CAP_CLEAR(SDMA_AHG);
		return 0;
	}
	if (mod_num_sdma &&
	    /* can't exceed chip support */
	    mod_num_sdma <= chip_sdma_engines(dd) &&
	    /* count must be >= vls */
	    mod_num_sdma >= num_vls)
		num_engines = mod_num_sdma;

	dd_dev_info(dd, "SDMA mod_num_sdma: %u\n", mod_num_sdma);
	dd_dev_info(dd, "SDMA chip_sdma_engines: %u\n", chip_sdma_engines(dd));
	dd_dev_info(dd, "SDMA chip_sdma_mem_size: %u\n",
		    chip_sdma_mem_size(dd));

	per_sdma_credits =
		chip_sdma_mem_size(dd) / (num_engines * SDMA_BLOCK_SIZE);

	/* set up freeze waitqueue */
	init_waitqueue_head(&dd->sdma_unfreeze_wq);
	atomic_set(&dd->sdma_unfreeze_count, 0);

	descq_cnt = sdma_get_descq_cnt();
	dd_dev_info(dd, "SDMA engines %zu descq_cnt %u\n",
		    num_engines, descq_cnt);

	/* alloc memory for array of send engines */
	dd->per_sdma = kcalloc_node(num_engines, sizeof(*dd->per_sdma),
				    GFP_KERNEL, dd->node);
	if (!dd->per_sdma)
		return ret;

	idle_cnt = ns_to_cclock(dd, idle_cnt);
	if (idle_cnt)
		dd->default_desc1 =
			SDMA_DESC1_HEAD_TO_HOST_FLAG;
	else
		dd->default_desc1 =
			SDMA_DESC1_INT_REQ_FLAG;

	if (!sdma_desct_intr)
		sdma_desct_intr = SDMA_DESC_INTR;

	/* Allocate memory for SendDMA descriptor FIFOs */
	for (this_idx = 0; this_idx < num_engines; ++this_idx) {
		sde = &dd->per_sdma[this_idx];
		sde->dd = dd;
		sde->ppd = ppd;
		sde->this_idx = this_idx;
		sde->descq_cnt = descq_cnt;
		sde->desc_avail = sdma_descq_freecnt(sde);
		sde->sdma_shift = ilog2(descq_cnt);
		sde->sdma_mask = (1 << sde->sdma_shift) - 1;

		/* Create a mask specifically for each interrupt source */
		sde->int_mask = (u64)1 << (0 * TXE_NUM_SDMA_ENGINES +
					   this_idx);
		sde->progress_mask = (u64)1 << (1 * TXE_NUM_SDMA_ENGINES +
						this_idx);
		sde->idle_mask = (u64)1 << (2 * TXE_NUM_SDMA_ENGINES +
					    this_idx);
		/* Create a combined mask to cover all 3 interrupt sources */
		sde->imask = sde->int_mask | sde->progress_mask |
			     sde->idle_mask;

		spin_lock_init(&sde->tail_lock);
		seqlock_init(&sde->head_lock);
		spin_lock_init(&sde->senddmactrl_lock);
		spin_lock_init(&sde->flushlist_lock);
		seqlock_init(&sde->waitlock);
		/* insure there is always a zero bit */
		sde->ahg_bits = 0xfffffffe00000000ULL;

		sdma_set_state(sde, sdma_state_s00_hw_down);

		/* set up reference counting */
		kref_init(&sde->state.kref);
		init_completion(&sde->state.comp);

		INIT_LIST_HEAD(&sde->flushlist);
		INIT_LIST_HEAD(&sde->dmawait);

		sde->tail_csr =
			get_kctxt_csr_addr(dd, this_idx, SD(TAIL));

		tasklet_init(&sde->sdma_hw_clean_up_task, sdma_hw_clean_up_task,
			     (unsigned long)sde);

		tasklet_init(&sde->sdma_sw_clean_up_task, sdma_sw_clean_up_task,
			     (unsigned long)sde);
		INIT_WORK(&sde->err_halt_worker, sdma_err_halt_wait);
		INIT_WORK(&sde->flush_worker, sdma_field_flush);

		sde->progress_check_head = 0;

		timer_setup(&sde->err_progress_check_timer,
			    sdma_err_progress_check, 0);

		sde->descq = dma_alloc_coherent(&dd->pcidev->dev,
						descq_cnt * sizeof(u64[2]),
						&sde->descq_phys, GFP_KERNEL);
		if (!sde->descq)
			goto bail;
		sde->tx_ring =
			kvzalloc_node(array_size(descq_cnt,
						 sizeof(struct sdma_txreq *)),
				      GFP_KERNEL, dd->node);
		if (!sde->tx_ring)
			goto bail;
	}

	dd->sdma_heads_size = L1_CACHE_BYTES * num_engines;
	/* Allocate memory for DMA of head registers to memory */
	dd->sdma_heads_dma = dma_alloc_coherent(&dd->pcidev->dev,
						dd->sdma_heads_size,
						&dd->sdma_heads_phys,
						GFP_KERNEL);
	if (!dd->sdma_heads_dma) {
		dd_dev_err(dd, "failed to allocate SendDMA head memory\n");
		goto bail;
	}

	/* Allocate memory for pad */
	dd->sdma_pad_dma = dma_alloc_coherent(&dd->pcidev->dev, SDMA_PAD,
					      &dd->sdma_pad_phys, GFP_KERNEL);
	if (!dd->sdma_pad_dma) {
		dd_dev_err(dd, "failed to allocate SendDMA pad memory\n");
		goto bail;
	}

	/* assign each engine to different cacheline and init registers */
	curr_head = (void *)dd->sdma_heads_dma;
	for (this_idx = 0; this_idx < num_engines; ++this_idx) {
		unsigned long phys_offset;

		sde = &dd->per_sdma[this_idx];

		sde->head_dma = curr_head;
		curr_head += L1_CACHE_BYTES;
		phys_offset = (unsigned long)sde->head_dma -
			      (unsigned long)dd->sdma_heads_dma;
		sde->head_phys = dd->sdma_heads_phys + phys_offset;
		init_sdma_regs(sde, per_sdma_credits, idle_cnt);
	}
	dd->flags |= HFI1_HAS_SEND_DMA;
	dd->flags |= idle_cnt ? HFI1_HAS_SDMA_TIMEOUT : 0;
	dd->num_sdma = num_engines;
	ret = sdma_map_init(dd, port, ppd->vls_operational, NULL);
	if (ret < 0)
		goto bail;

	tmp_sdma_rht = kzalloc(sizeof(*tmp_sdma_rht), GFP_KERNEL);
	if (!tmp_sdma_rht) {
		ret = -ENOMEM;
		goto bail;
	}

	ret = rhashtable_init(tmp_sdma_rht, &sdma_rht_params);
	if (ret < 0) {
		kfree(tmp_sdma_rht);
		goto bail;
	}

	dd->sdma_rht = tmp_sdma_rht;

	dd_dev_info(dd, "SDMA num_sdma: %u\n", dd->num_sdma);
	return 0;

bail:
	sdma_clean(dd, num_engines);
	return ret;
}
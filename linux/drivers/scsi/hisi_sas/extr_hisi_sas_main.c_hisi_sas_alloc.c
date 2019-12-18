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
struct hisi_sas_slot_dif_buf_table {int dummy; } ;
struct hisi_sas_slot_buf_table {int dummy; } ;
struct hisi_sas_slot {int buf_dma; int idx; void* buf; } ;
struct hisi_sas_sata_breakpoint {int dummy; } ;
struct hisi_sas_itct {int dummy; } ;
struct hisi_sas_iost {int dummy; } ;
struct hisi_sas_initial_fis {int dummy; } ;
struct hisi_sas_dq {int id; struct hisi_hba* hisi_hba; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct hisi_sas_cq {int id; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_sas_breakpoint {int dummy; } ;
struct hisi_hba {int n_phy; int queue_count; int* cmd_hdr_dma; int* complete_hdr_dma; int itct_dma; int prot_mask; int iost_dma; int breakpoint_dma; int slot_index_count; int initial_fis_dma; int sata_breakpoint_dma; int /*<<< orphan*/  wq; int /*<<< orphan*/  last_slot_index; void* sata_breakpoint; void* initial_fis; int /*<<< orphan*/  slot_index_tags; void* breakpoint; void* iost; struct hisi_sas_slot* slot_info; void* itct; void** complete_hdr; TYPE_3__* hw; void** cmd_hdr; struct hisi_sas_dq* dq; struct hisi_sas_cq* cq; TYPE_2__* devices; TYPE_1__* port; int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int complete_hdr_size; } ;
struct TYPE_5__ {int device_id; int /*<<< orphan*/  dev_status; int /*<<< orphan*/  dev_type; } ;
struct TYPE_4__ {int id; scalar_t__ port_attached; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HISI_SAS_DEV_INIT ; 
 int HISI_SAS_DIX_PROT_MASK ; 
 int HISI_SAS_MAX_COMMANDS ; 
 int HISI_SAS_MAX_DEVICES ; 
 int HISI_SAS_MAX_ITCT_ENTRIES ; 
 int HISI_SAS_MAX_PHYS ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  HISI_SAS_UNRESERVED_IPTT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct hisi_sas_slot* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* dmam_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_init (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  hisi_sas_slot_index_init (struct hisi_hba*) ; 
 int /*<<< orphan*/  lcm (int,int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hisi_sas_alloc(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int i, j, s, max_command_entries = HISI_SAS_MAX_COMMANDS;
	int max_command_entries_ru, sz_slot_buf_ru;
	int blk_cnt, slots_per_blk;

	sema_init(&hisi_hba->sem, 1);
	spin_lock_init(&hisi_hba->lock);
	for (i = 0; i < hisi_hba->n_phy; i++) {
		hisi_sas_phy_init(hisi_hba, i);
		hisi_hba->port[i].port_attached = 0;
		hisi_hba->port[i].id = -1;
	}

	for (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		hisi_hba->devices[i].dev_type = SAS_PHY_UNUSED;
		hisi_hba->devices[i].device_id = i;
		hisi_hba->devices[i].dev_status = HISI_SAS_DEV_INIT;
	}

	for (i = 0; i < hisi_hba->queue_count; i++) {
		struct hisi_sas_cq *cq = &hisi_hba->cq[i];
		struct hisi_sas_dq *dq = &hisi_hba->dq[i];

		/* Completion queue structure */
		cq->id = i;
		cq->hisi_hba = hisi_hba;

		/* Delivery queue structure */
		spin_lock_init(&dq->lock);
		INIT_LIST_HEAD(&dq->list);
		dq->id = i;
		dq->hisi_hba = hisi_hba;

		/* Delivery queue */
		s = sizeof(struct hisi_sas_cmd_hdr) * HISI_SAS_QUEUE_SLOTS;
		hisi_hba->cmd_hdr[i] = dmam_alloc_coherent(dev, s,
						&hisi_hba->cmd_hdr_dma[i],
						GFP_KERNEL);
		if (!hisi_hba->cmd_hdr[i])
			goto err_out;

		/* Completion queue */
		s = hisi_hba->hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
		hisi_hba->complete_hdr[i] = dmam_alloc_coherent(dev, s,
						&hisi_hba->complete_hdr_dma[i],
						GFP_KERNEL);
		if (!hisi_hba->complete_hdr[i])
			goto err_out;
	}

	s = HISI_SAS_MAX_ITCT_ENTRIES * sizeof(struct hisi_sas_itct);
	hisi_hba->itct = dmam_alloc_coherent(dev, s, &hisi_hba->itct_dma,
					     GFP_KERNEL);
	if (!hisi_hba->itct)
		goto err_out;

	hisi_hba->slot_info = devm_kcalloc(dev, max_command_entries,
					   sizeof(struct hisi_sas_slot),
					   GFP_KERNEL);
	if (!hisi_hba->slot_info)
		goto err_out;

	/* roundup to avoid overly large block size */
	max_command_entries_ru = roundup(max_command_entries, 64);
	if (hisi_hba->prot_mask & HISI_SAS_DIX_PROT_MASK)
		sz_slot_buf_ru = sizeof(struct hisi_sas_slot_dif_buf_table);
	else
		sz_slot_buf_ru = sizeof(struct hisi_sas_slot_buf_table);
	sz_slot_buf_ru = roundup(sz_slot_buf_ru, 64);
	s = max(lcm(max_command_entries_ru, sz_slot_buf_ru), PAGE_SIZE);
	blk_cnt = (max_command_entries_ru * sz_slot_buf_ru) / s;
	slots_per_blk = s / sz_slot_buf_ru;

	for (i = 0; i < blk_cnt; i++) {
		int slot_index = i * slots_per_blk;
		dma_addr_t buf_dma;
		void *buf;

		buf = dmam_alloc_coherent(dev, s, &buf_dma,
					  GFP_KERNEL);
		if (!buf)
			goto err_out;

		for (j = 0; j < slots_per_blk; j++, slot_index++) {
			struct hisi_sas_slot *slot;

			slot = &hisi_hba->slot_info[slot_index];
			slot->buf = buf;
			slot->buf_dma = buf_dma;
			slot->idx = slot_index;

			buf += sz_slot_buf_ru;
			buf_dma += sz_slot_buf_ru;
		}
	}

	s = max_command_entries * sizeof(struct hisi_sas_iost);
	hisi_hba->iost = dmam_alloc_coherent(dev, s, &hisi_hba->iost_dma,
					     GFP_KERNEL);
	if (!hisi_hba->iost)
		goto err_out;

	s = max_command_entries * sizeof(struct hisi_sas_breakpoint);
	hisi_hba->breakpoint = dmam_alloc_coherent(dev, s,
						   &hisi_hba->breakpoint_dma,
						   GFP_KERNEL);
	if (!hisi_hba->breakpoint)
		goto err_out;

	hisi_hba->slot_index_count = max_command_entries;
	s = hisi_hba->slot_index_count / BITS_PER_BYTE;
	hisi_hba->slot_index_tags = devm_kzalloc(dev, s, GFP_KERNEL);
	if (!hisi_hba->slot_index_tags)
		goto err_out;

	s = sizeof(struct hisi_sas_initial_fis) * HISI_SAS_MAX_PHYS;
	hisi_hba->initial_fis = dmam_alloc_coherent(dev, s,
						    &hisi_hba->initial_fis_dma,
						    GFP_KERNEL);
	if (!hisi_hba->initial_fis)
		goto err_out;

	s = HISI_SAS_MAX_ITCT_ENTRIES * sizeof(struct hisi_sas_sata_breakpoint);
	hisi_hba->sata_breakpoint = dmam_alloc_coherent(dev, s,
					&hisi_hba->sata_breakpoint_dma,
					GFP_KERNEL);
	if (!hisi_hba->sata_breakpoint)
		goto err_out;

	hisi_sas_slot_index_init(hisi_hba);
	hisi_hba->last_slot_index = HISI_SAS_UNRESERVED_IPTT;

	hisi_hba->wq = create_singlethread_workqueue(dev_name(dev));
	if (!hisi_hba->wq) {
		dev_err(dev, "sas_alloc: failed to create workqueue\n");
		goto err_out;
	}

	return 0;
err_out:
	return -ENOMEM;
}
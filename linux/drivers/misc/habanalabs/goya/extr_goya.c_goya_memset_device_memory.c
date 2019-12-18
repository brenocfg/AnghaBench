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
typedef  int u64 ;
typedef  int u32 ;
struct packet_msg_prot {int dummy; } ;
struct packet_lin_dma {void* tsize; void* dst_addr; void* src_addr; void* ctl; } ;
struct hl_device {int /*<<< orphan*/  kernel_cb_mgr; int /*<<< orphan*/  dev; } ;
struct hl_cs_job {int user_cb_size; int job_cb_size; struct hl_cb* patched_cb; struct hl_cb* user_cb; int /*<<< orphan*/  hw_queue_id; scalar_t__ id; } ;
struct hl_cb {int id; int /*<<< orphan*/  cs_cnt; scalar_t__ kernel_address; } ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int,int) ; 
 int DMA_HOST_TO_DRAM ; 
 int DMA_HOST_TO_SRAM ; 
 int ENOMEM ; 
 int GOYA_PKT_CTL_MB_SHIFT ; 
 int GOYA_PKT_CTL_OPCODE_SHIFT ; 
 int GOYA_PKT_CTL_RB_SHIFT ; 
 int GOYA_PKT_LIN_DMA_CTL_DMA_DIR_SHIFT ; 
 int GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT ; 
 int GOYA_PKT_LIN_DMA_CTL_WO_SHIFT ; 
 int /*<<< orphan*/  GOYA_QUEUE_ID_DMA_0 ; 
 int PACKET_LIN_DMA ; 
 int PAGE_SHIFT ; 
 int SZ_2G ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int goya_send_job_on_qman0 (struct hl_device*,struct hl_cs_job*) ; 
 int /*<<< orphan*/  hl_cb_destroy (struct hl_device*,int /*<<< orphan*/ *,int) ; 
 struct hl_cb* hl_cb_kernel_create (struct hl_device*,int) ; 
 int /*<<< orphan*/  hl_cb_put (struct hl_cb*) ; 
 struct hl_cs_job* hl_cs_allocate_job (struct hl_device*,int) ; 
 int /*<<< orphan*/  hl_debugfs_add_job (struct hl_device*,struct hl_cs_job*) ; 
 int /*<<< orphan*/  hl_debugfs_remove_job (struct hl_device*,struct hl_cs_job*) ; 
 int /*<<< orphan*/  kfree (struct hl_cs_job*) ; 
 int /*<<< orphan*/  memset (struct packet_lin_dma*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int goya_memset_device_memory(struct hl_device *hdev, u64 addr, u64 size,
				u64 val, bool is_dram)
{
	struct packet_lin_dma *lin_dma_pkt;
	struct hl_cs_job *job;
	u32 cb_size, ctl;
	struct hl_cb *cb;
	int rc, lin_dma_pkts_cnt;

	lin_dma_pkts_cnt = DIV_ROUND_UP_ULL(size, SZ_2G);
	cb_size = lin_dma_pkts_cnt * sizeof(struct packet_lin_dma) +
						sizeof(struct packet_msg_prot);
	cb = hl_cb_kernel_create(hdev, cb_size);
	if (!cb)
		return -ENOMEM;

	lin_dma_pkt = (struct packet_lin_dma *) (uintptr_t) cb->kernel_address;

	do {
		memset(lin_dma_pkt, 0, sizeof(*lin_dma_pkt));

		ctl = ((PACKET_LIN_DMA << GOYA_PKT_CTL_OPCODE_SHIFT) |
				(1 << GOYA_PKT_LIN_DMA_CTL_MEMSET_SHIFT) |
				(1 << GOYA_PKT_LIN_DMA_CTL_WO_SHIFT) |
				(1 << GOYA_PKT_CTL_RB_SHIFT) |
				(1 << GOYA_PKT_CTL_MB_SHIFT));
		ctl |= (is_dram ? DMA_HOST_TO_DRAM : DMA_HOST_TO_SRAM) <<
				GOYA_PKT_LIN_DMA_CTL_DMA_DIR_SHIFT;
		lin_dma_pkt->ctl = cpu_to_le32(ctl);

		lin_dma_pkt->src_addr = cpu_to_le64(val);
		lin_dma_pkt->dst_addr = cpu_to_le64(addr);
		if (lin_dma_pkts_cnt > 1)
			lin_dma_pkt->tsize = cpu_to_le32(SZ_2G);
		else
			lin_dma_pkt->tsize = cpu_to_le32(size);

		size -= SZ_2G;
		addr += SZ_2G;
		lin_dma_pkt++;
	} while (--lin_dma_pkts_cnt);

	job = hl_cs_allocate_job(hdev, true);
	if (!job) {
		dev_err(hdev->dev, "Failed to allocate a new job\n");
		rc = -ENOMEM;
		goto release_cb;
	}

	job->id = 0;
	job->user_cb = cb;
	job->user_cb->cs_cnt++;
	job->user_cb_size = cb_size;
	job->hw_queue_id = GOYA_QUEUE_ID_DMA_0;
	job->patched_cb = job->user_cb;
	job->job_cb_size = job->user_cb_size;

	hl_debugfs_add_job(hdev, job);

	rc = goya_send_job_on_qman0(hdev, job);

	hl_cb_put(job->patched_cb);

	hl_debugfs_remove_job(hdev, job);
	kfree(job);
	cb->cs_cnt--;

release_cb:
	hl_cb_put(cb);
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb->id << PAGE_SHIFT);

	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_12__ {int version; int max_flowrings; int max_submissionrings; int max_completionrings; struct brcmf_pcie_ringbuf* flowrings; struct brcmf_pcie_ringbuf** commonrings; scalar_t__ ring_info_addr; } ;
struct brcmf_pciedev_info {int dma_idx_sz; int idxbuf_sz; TYPE_6__ shared; scalar_t__ tcm; scalar_t__ idxbuf_dmahandle; int /*<<< orphan*/  read_ptr; int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  idxbuf; TYPE_1__* pdev; } ;
struct brcmf_pcie_ringbuf {int w_idx_addr; int r_idx_addr; int id; int /*<<< orphan*/  commonring; struct brcmf_pciedev_info* devinfo; } ;
struct TYPE_11__ {void* high_addr; void* low_addr; } ;
struct TYPE_10__ {void* high_addr; void* low_addr; } ;
struct TYPE_9__ {void* high_addr; void* low_addr; } ;
struct TYPE_8__ {void* high_addr; void* low_addr; } ;
struct brcmf_pcie_dhi_ringinfo {int /*<<< orphan*/  ringmem; TYPE_5__ d2h_r_idx_hostaddr; TYPE_4__ d2h_w_idx_hostaddr; TYPE_3__ h2d_r_idx_hostaddr; TYPE_2__ h2d_w_idx_hostaddr; int /*<<< orphan*/  h2d_r_idx_ptr; int /*<<< orphan*/  h2d_w_idx_ptr; int /*<<< orphan*/  d2h_r_idx_ptr; int /*<<< orphan*/  d2h_w_idx_ptr; int /*<<< orphan*/  max_flowrings; int /*<<< orphan*/  max_completionrings; int /*<<< orphan*/  max_submissionrings; } ;
struct brcmf_bus {int dummy; } ;
typedef  int /*<<< orphan*/  ringinfo ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMF_H2D_MSGRING_FLOWRING_IDSTART ; 
 int BRCMF_NROF_COMMON_MSGRINGS ; 
 int BRCMF_NROF_D2H_COMMON_MSGRINGS ; 
 int BRCMF_NROF_H2D_COMMON_MSGRINGS ; 
 scalar_t__ BRCMF_RING_MEM_SZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_commonring_register_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_pcie_ringbuf*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*) ; 
 struct brcmf_pcie_ringbuf* brcmf_pcie_alloc_dma_and_ring (struct brcmf_pciedev_info*,int,int) ; 
 int /*<<< orphan*/  brcmf_pcie_read_idx ; 
 int /*<<< orphan*/  brcmf_pcie_read_tcm16 ; 
 int /*<<< orphan*/  brcmf_pcie_release_ringbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_ring_bell ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_update_rptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_update_wptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_write_rptr ; 
 int /*<<< orphan*/  brcmf_pcie_ring_mb_write_wptr ; 
 int /*<<< orphan*/  brcmf_pcie_write_idx ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm16 ; 
 void* cpu_to_le32 (int) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct brcmf_pcie_ringbuf* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (struct brcmf_pcie_dhi_ringinfo*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,struct brcmf_pcie_dhi_ringinfo*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_pcie_init_ringbuffers(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	struct brcmf_pcie_ringbuf *ring;
	struct brcmf_pcie_ringbuf *rings;
	u32 d2h_w_idx_ptr;
	u32 d2h_r_idx_ptr;
	u32 h2d_w_idx_ptr;
	u32 h2d_r_idx_ptr;
	u32 ring_mem_ptr;
	u32 i;
	u64 address;
	u32 bufsz;
	u8 idx_offset;
	struct brcmf_pcie_dhi_ringinfo ringinfo;
	u16 max_flowrings;
	u16 max_submissionrings;
	u16 max_completionrings;

	memcpy_fromio(&ringinfo, devinfo->tcm + devinfo->shared.ring_info_addr,
		      sizeof(ringinfo));
	if (devinfo->shared.version >= 6) {
		max_submissionrings = le16_to_cpu(ringinfo.max_submissionrings);
		max_flowrings = le16_to_cpu(ringinfo.max_flowrings);
		max_completionrings = le16_to_cpu(ringinfo.max_completionrings);
	} else {
		max_submissionrings = le16_to_cpu(ringinfo.max_flowrings);
		max_flowrings = max_submissionrings -
				BRCMF_NROF_H2D_COMMON_MSGRINGS;
		max_completionrings = BRCMF_NROF_D2H_COMMON_MSGRINGS;
	}

	if (devinfo->dma_idx_sz != 0) {
		bufsz = (max_submissionrings + max_completionrings) *
			devinfo->dma_idx_sz * 2;
		devinfo->idxbuf = dma_alloc_coherent(&devinfo->pdev->dev, bufsz,
						     &devinfo->idxbuf_dmahandle,
						     GFP_KERNEL);
		if (!devinfo->idxbuf)
			devinfo->dma_idx_sz = 0;
	}

	if (devinfo->dma_idx_sz == 0) {
		d2h_w_idx_ptr = le32_to_cpu(ringinfo.d2h_w_idx_ptr);
		d2h_r_idx_ptr = le32_to_cpu(ringinfo.d2h_r_idx_ptr);
		h2d_w_idx_ptr = le32_to_cpu(ringinfo.h2d_w_idx_ptr);
		h2d_r_idx_ptr = le32_to_cpu(ringinfo.h2d_r_idx_ptr);
		idx_offset = sizeof(u32);
		devinfo->write_ptr = brcmf_pcie_write_tcm16;
		devinfo->read_ptr = brcmf_pcie_read_tcm16;
		brcmf_dbg(PCIE, "Using TCM indices\n");
	} else {
		memset(devinfo->idxbuf, 0, bufsz);
		devinfo->idxbuf_sz = bufsz;
		idx_offset = devinfo->dma_idx_sz;
		devinfo->write_ptr = brcmf_pcie_write_idx;
		devinfo->read_ptr = brcmf_pcie_read_idx;

		h2d_w_idx_ptr = 0;
		address = (u64)devinfo->idxbuf_dmahandle;
		ringinfo.h2d_w_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.h2d_w_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		h2d_r_idx_ptr = h2d_w_idx_ptr +
				max_submissionrings * idx_offset;
		address += max_submissionrings * idx_offset;
		ringinfo.h2d_r_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.h2d_r_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		d2h_w_idx_ptr = h2d_r_idx_ptr +
				max_submissionrings * idx_offset;
		address += max_submissionrings * idx_offset;
		ringinfo.d2h_w_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.d2h_w_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		d2h_r_idx_ptr = d2h_w_idx_ptr +
				max_completionrings * idx_offset;
		address += max_completionrings * idx_offset;
		ringinfo.d2h_r_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.d2h_r_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		memcpy_toio(devinfo->tcm + devinfo->shared.ring_info_addr,
			    &ringinfo, sizeof(ringinfo));
		brcmf_dbg(PCIE, "Using host memory indices\n");
	}

	ring_mem_ptr = le32_to_cpu(ringinfo.ringmem);

	for (i = 0; i < BRCMF_NROF_H2D_COMMON_MSGRINGS; i++) {
		ring = brcmf_pcie_alloc_dma_and_ring(devinfo, i, ring_mem_ptr);
		if (!ring)
			goto fail;
		ring->w_idx_addr = h2d_w_idx_ptr;
		ring->r_idx_addr = h2d_r_idx_ptr;
		ring->id = i;
		devinfo->shared.commonrings[i] = ring;

		h2d_w_idx_ptr += idx_offset;
		h2d_r_idx_ptr += idx_offset;
		ring_mem_ptr += BRCMF_RING_MEM_SZ;
	}

	for (i = BRCMF_NROF_H2D_COMMON_MSGRINGS;
	     i < BRCMF_NROF_COMMON_MSGRINGS; i++) {
		ring = brcmf_pcie_alloc_dma_and_ring(devinfo, i, ring_mem_ptr);
		if (!ring)
			goto fail;
		ring->w_idx_addr = d2h_w_idx_ptr;
		ring->r_idx_addr = d2h_r_idx_ptr;
		ring->id = i;
		devinfo->shared.commonrings[i] = ring;

		d2h_w_idx_ptr += idx_offset;
		d2h_r_idx_ptr += idx_offset;
		ring_mem_ptr += BRCMF_RING_MEM_SZ;
	}

	devinfo->shared.max_flowrings = max_flowrings;
	devinfo->shared.max_submissionrings = max_submissionrings;
	devinfo->shared.max_completionrings = max_completionrings;
	rings = kcalloc(max_flowrings, sizeof(*ring), GFP_KERNEL);
	if (!rings)
		goto fail;

	brcmf_dbg(PCIE, "Nr of flowrings is %d\n", max_flowrings);

	for (i = 0; i < max_flowrings; i++) {
		ring = &rings[i];
		ring->devinfo = devinfo;
		ring->id = i + BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
		brcmf_commonring_register_cb(&ring->commonring,
					     brcmf_pcie_ring_mb_ring_bell,
					     brcmf_pcie_ring_mb_update_rptr,
					     brcmf_pcie_ring_mb_update_wptr,
					     brcmf_pcie_ring_mb_write_rptr,
					     brcmf_pcie_ring_mb_write_wptr,
					     ring);
		ring->w_idx_addr = h2d_w_idx_ptr;
		ring->r_idx_addr = h2d_r_idx_ptr;
		h2d_w_idx_ptr += idx_offset;
		h2d_r_idx_ptr += idx_offset;
	}
	devinfo->shared.flowrings = rings;

	return 0;

fail:
	brcmf_err(bus, "Allocating ring buffers failed\n");
	brcmf_pcie_release_ringbuffers(devinfo);
	return -ENOMEM;
}
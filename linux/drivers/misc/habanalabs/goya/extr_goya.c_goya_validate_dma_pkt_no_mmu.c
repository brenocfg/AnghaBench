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
typedef  int u32 ;
struct packet_lin_dma {scalar_t__ tsize; scalar_t__ ctl; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_cs_parser {int dummy; } ;
typedef  enum goya_dma_direction { ____Placeholder_goya_dma_direction } goya_dma_direction ;

/* Variables and functions */
 int DMA_DRAM_TO_SRAM ; 
 int DMA_SRAM_TO_DRAM ; 
 int EINVAL ; 
 int GOYA_PKT_LIN_DMA_CTL_DMA_DIR_MASK ; 
 int GOYA_PKT_LIN_DMA_CTL_DMA_DIR_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int goya_validate_dma_pkt_host (struct hl_device*,struct hl_cs_parser*,struct packet_lin_dma*) ; 
 int goya_validate_dma_pkt_no_host (struct hl_device*,struct hl_cs_parser*,struct packet_lin_dma*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_validate_dma_pkt_no_mmu(struct hl_device *hdev,
				struct hl_cs_parser *parser,
				struct packet_lin_dma *user_dma_pkt)
{
	enum goya_dma_direction user_dir;
	u32 ctl;
	int rc;

	dev_dbg(hdev->dev, "DMA packet details:\n");
	dev_dbg(hdev->dev, "source == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->src_addr));
	dev_dbg(hdev->dev, "destination == 0x%llx\n",
		le64_to_cpu(user_dma_pkt->dst_addr));
	dev_dbg(hdev->dev, "size == %u\n", le32_to_cpu(user_dma_pkt->tsize));

	ctl = le32_to_cpu(user_dma_pkt->ctl);
	user_dir = (ctl & GOYA_PKT_LIN_DMA_CTL_DMA_DIR_MASK) >>
			GOYA_PKT_LIN_DMA_CTL_DMA_DIR_SHIFT;

	/*
	 * Special handling for DMA with size 0. The H/W has a bug where
	 * this can cause the QMAN DMA to get stuck, so block it here.
	 */
	if (user_dma_pkt->tsize == 0) {
		dev_err(hdev->dev,
			"Got DMA with size 0, might reset the device\n");
		return -EINVAL;
	}

	if ((user_dir == DMA_DRAM_TO_SRAM) || (user_dir == DMA_SRAM_TO_DRAM))
		rc = goya_validate_dma_pkt_no_host(hdev, parser, user_dma_pkt);
	else
		rc = goya_validate_dma_pkt_host(hdev, parser, user_dma_pkt);

	return rc;
}
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
typedef  int u32 ;
struct TYPE_3__ {int src_addr_widths; int dst_addr_widths; } ;
struct sun6i_dma_dev {TYPE_2__* cfg; TYPE_1__ slave; } ;
struct dma_slave_config {int src_addr_width; int dst_addr_width; int src_maxburst; int dst_maxburst; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
struct TYPE_4__ {int src_burst_lengths; int dst_burst_lengths; int /*<<< orphan*/  (* set_burst_length ) (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int DMA_CHAN_CFG_DST_WIDTH (int /*<<< orphan*/ ) ; 
 int DMA_CHAN_CFG_SRC_WIDTH (int /*<<< orphan*/ ) ; 
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_UNDEFINED ; 
 int EINVAL ; 
 int /*<<< orphan*/  convert_burst (int) ; 
 int /*<<< orphan*/  convert_buswidth (int) ; 
 int /*<<< orphan*/  stub1 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_config(struct sun6i_dma_dev *sdev,
			struct dma_slave_config *sconfig,
			enum dma_transfer_direction direction,
			u32 *p_cfg)
{
	enum dma_slave_buswidth src_addr_width, dst_addr_width;
	u32 src_maxburst, dst_maxburst;
	s8 src_width, dst_width, src_burst, dst_burst;

	src_addr_width = sconfig->src_addr_width;
	dst_addr_width = sconfig->dst_addr_width;
	src_maxburst = sconfig->src_maxburst;
	dst_maxburst = sconfig->dst_maxburst;

	switch (direction) {
	case DMA_MEM_TO_DEV:
		if (src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		src_maxburst = src_maxburst ? src_maxburst : 8;
		break;
	case DMA_DEV_TO_MEM:
		if (dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dst_maxburst = dst_maxburst ? dst_maxburst : 8;
		break;
	default:
		return -EINVAL;
	}

	if (!(BIT(src_addr_width) & sdev->slave.src_addr_widths))
		return -EINVAL;
	if (!(BIT(dst_addr_width) & sdev->slave.dst_addr_widths))
		return -EINVAL;
	if (!(BIT(src_maxburst) & sdev->cfg->src_burst_lengths))
		return -EINVAL;
	if (!(BIT(dst_maxburst) & sdev->cfg->dst_burst_lengths))
		return -EINVAL;

	src_width = convert_buswidth(src_addr_width);
	dst_width = convert_buswidth(dst_addr_width);
	dst_burst = convert_burst(dst_maxburst);
	src_burst = convert_burst(src_maxburst);

	*p_cfg = DMA_CHAN_CFG_SRC_WIDTH(src_width) |
		DMA_CHAN_CFG_DST_WIDTH(dst_width);

	sdev->cfg->set_burst_length(p_cfg, src_burst, dst_burst);

	return 0;
}
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
struct saa7134_go7007 {int /*<<< orphan*/  top_dma; int /*<<< orphan*/  top; int /*<<< orphan*/  bottom_dma; int /*<<< orphan*/  bottom; } ;
struct saa7134_dev {TYPE_1__* pci; int /*<<< orphan*/  empress_dev; } ;
struct go7007 {int /*<<< orphan*/  vidq; struct saa7134_go7007* hpi_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  go7007_parse_video_stream (struct go7007*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_is_streaming (int /*<<< orphan*/ *) ; 
 struct go7007* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saa7134_go7007_irq_ts_done(struct saa7134_dev *dev,
						unsigned long status)
{
	struct go7007 *go = video_get_drvdata(dev->empress_dev);
	struct saa7134_go7007 *saa = go->hpi_context;

	if (!vb2_is_streaming(&go->vidq))
		return;
	if (0 != (status & 0x000f0000))
		pr_debug("saa7134-go7007: irq: lost %ld\n",
				(status >> 16) & 0x0f);
	if (status & 0x100000) {
		dma_sync_single_for_cpu(&dev->pci->dev,
					saa->bottom_dma, PAGE_SIZE, DMA_FROM_DEVICE);
		go7007_parse_video_stream(go, saa->bottom, PAGE_SIZE);
		saa_writel(SAA7134_RS_BA2(5), saa->bottom_dma);
	} else {
		dma_sync_single_for_cpu(&dev->pci->dev,
					saa->top_dma, PAGE_SIZE, DMA_FROM_DEVICE);
		go7007_parse_video_stream(go, saa->top, PAGE_SIZE);
		saa_writel(SAA7134_RS_BA1(5), saa->top_dma);
	}
}
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
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct ispstat_buffer {TYPE_2__ sgt; } ;
struct ispstat {TYPE_1__* isp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ISP_STAT_USES_DMAENGINE (struct ispstat*) ; 
 int /*<<< orphan*/  dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_stat_buf_sync_for_cpu(struct ispstat *stat,
				      struct ispstat_buffer *buf)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		return;

	dma_sync_sg_for_cpu(stat->isp->dev, buf->sgt.sgl,
			    buf->sgt.nents, DMA_FROM_DEVICE);
}
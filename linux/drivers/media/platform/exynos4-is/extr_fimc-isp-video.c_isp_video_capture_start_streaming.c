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
struct vb2_queue {int dummy; } ;
struct param_dma_output {scalar_t__ buffer_address; int /*<<< orphan*/  dma_out_mask; int /*<<< orphan*/  buffer_number; int /*<<< orphan*/  notify_dma_done; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdev; } ;
struct fimc_is_video {TYPE_2__ ve; TYPE_1__* format; int /*<<< orphan*/  buf_count; int /*<<< orphan*/  buf_mask; int /*<<< orphan*/  reqbufs_count; } ;
struct fimc_isp {int /*<<< orphan*/  state; struct fimc_is_video video_capture; } ;
struct fimc_is {scalar_t__ is_dma_p_region; } ;
struct TYPE_3__ {int /*<<< orphan*/  memplanes; } ;

/* Variables and functions */
 scalar_t__ DMA2_OUTPUT_ADDR_ARRAY_OFFS ; 
 int /*<<< orphan*/  DMA_OUTPUT_COMMAND_ENABLE ; 
 int /*<<< orphan*/  DMA_OUTPUT_NOTIFY_DMA_DONE_ENABLE ; 
 int /*<<< orphan*/  PARAM_ISP_DMA2_OUTPUT ; 
 int /*<<< orphan*/  ST_ISP_VID_CAP_BUF_PREP ; 
 int /*<<< orphan*/  ST_ISP_VID_CAP_STREAMING ; 
 int /*<<< orphan*/  __fimc_is_hw_update_param (struct fimc_is*,int /*<<< orphan*/ ) ; 
 struct param_dma_output* __get_isp_dma2 (struct fimc_is*) ; 
 int fimc_is_itf_s_param (struct fimc_is*,int) ; 
 int /*<<< orphan*/  fimc_is_mem_barrier () ; 
 int /*<<< orphan*/  fimc_is_set_param_bit (struct fimc_is*,int /*<<< orphan*/ ) ; 
 struct fimc_is* fimc_isp_to_is (struct fimc_isp*) ; 
 int fimc_pipeline_call (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp_dbg (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_stream ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fimc_isp* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int isp_video_capture_start_streaming(struct vb2_queue *q,
						unsigned int count)
{
	struct fimc_isp *isp = vb2_get_drv_priv(q);
	struct fimc_is *is = fimc_isp_to_is(isp);
	struct param_dma_output *dma = __get_isp_dma2(is);
	struct fimc_is_video *video = &isp->video_capture;
	int ret;

	if (!test_bit(ST_ISP_VID_CAP_BUF_PREP, &isp->state) ||
	    test_bit(ST_ISP_VID_CAP_STREAMING, &isp->state))
		return 0;


	dma->cmd = DMA_OUTPUT_COMMAND_ENABLE;
	dma->notify_dma_done = DMA_OUTPUT_NOTIFY_DMA_DONE_ENABLE;
	dma->buffer_address = is->is_dma_p_region +
				DMA2_OUTPUT_ADDR_ARRAY_OFFS;
	dma->buffer_number = video->reqbufs_count;
	dma->dma_out_mask = video->buf_mask;

	isp_dbg(2, &video->ve.vdev,
		"buf_count: %d, planes: %d, dma addr table: %#x\n",
		video->buf_count, video->format->memplanes,
		dma->buffer_address);

	fimc_is_mem_barrier();

	fimc_is_set_param_bit(is, PARAM_ISP_DMA2_OUTPUT);
	__fimc_is_hw_update_param(is, PARAM_ISP_DMA2_OUTPUT);

	ret = fimc_is_itf_s_param(is, false);
	if (ret < 0)
		return ret;

	ret = fimc_pipeline_call(&video->ve, set_stream, 1);
	if (ret < 0)
		return ret;

	set_bit(ST_ISP_VID_CAP_STREAMING, &isp->state);
	return ret;
}
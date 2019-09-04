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
struct v4l2_device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct ivtv** sliced_mpeg_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdl; } ;
struct ivtv {int v4l2_cap; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  card_name; TYPE_2__ vbi; TYPE_3__* pdev; scalar_t__ base_addr; scalar_t__ has_cx23415; TYPE_1__ cxhdl; int /*<<< orphan*/  irq_worker_task; int /*<<< orphan*/  irq_worker; int /*<<< orphan*/  dma_timer; int /*<<< orphan*/ * streams; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  decoding; int /*<<< orphan*/  capturing; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 scalar_t__ IVTV_DECODER_OFFSET ; 
 int /*<<< orphan*/  IVTV_DECODER_SIZE ; 
 int IVTV_DEC_STREAM_TYPE_MPG ; 
 int IVTV_DEC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  IVTV_ENCODER_SIZE ; 
 int /*<<< orphan*/  IVTV_F_I_DEC_YUV ; 
 int /*<<< orphan*/  IVTV_F_I_INITED ; 
 int /*<<< orphan*/  IVTV_HW_SAA7127 ; 
 scalar_t__ IVTV_REG_OFFSET ; 
 int /*<<< orphan*/  IVTV_REG_SIZE ; 
 int IVTV_VBI_FRAMES ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int V4L2_DEC_CMD_STOP_IMMEDIATELY ; 
 int V4L2_DEC_CMD_STOP_TO_BLACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct v4l2_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_ivtv_i2c (struct ivtv*) ; 
 int /*<<< orphan*/  flush_request_modules (struct ivtv*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_halt_firmware (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_iounmap (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_set_irq_mask (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_stop_all_captures (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_stop_v4l2_decode_stream (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_streams_cleanup (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_udma_free (struct ivtv*) ; 
 int /*<<< orphan*/  kfree (struct ivtv*) ; 
 int /*<<< orphan*/  kthread_flush_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ivtv* to_ivtv (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void ivtv_remove(struct pci_dev *pdev)
{
	struct v4l2_device *v4l2_dev = dev_get_drvdata(&pdev->dev);
	struct ivtv *itv = to_ivtv(v4l2_dev);
	int i;

	IVTV_DEBUG_INFO("Removing card\n");

	flush_request_modules(itv);

	if (test_bit(IVTV_F_I_INITED, &itv->i_flags)) {
		/* Stop all captures */
		IVTV_DEBUG_INFO("Stopping all streams\n");
		if (atomic_read(&itv->capturing) > 0)
			ivtv_stop_all_captures(itv);

		/* Stop all decoding */
		IVTV_DEBUG_INFO("Stopping decoding\n");

		/* Turn off the TV-out */
		if (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT)
			ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 0);
		if (atomic_read(&itv->decoding) > 0) {
			int type;

			if (test_bit(IVTV_F_I_DEC_YUV, &itv->i_flags))
				type = IVTV_DEC_STREAM_TYPE_YUV;
			else
				type = IVTV_DEC_STREAM_TYPE_MPG;
			ivtv_stop_v4l2_decode_stream(&itv->streams[type],
				V4L2_DEC_CMD_STOP_TO_BLACK | V4L2_DEC_CMD_STOP_IMMEDIATELY, 0);
		}
		ivtv_halt_firmware(itv);
	}

	/* Interrupts */
	ivtv_set_irq_mask(itv, 0xffffffff);
	del_timer_sync(&itv->dma_timer);

	/* Kill irq worker */
	kthread_flush_worker(&itv->irq_worker);
	kthread_stop(itv->irq_worker_task);

	ivtv_streams_cleanup(itv);
	ivtv_udma_free(itv);

	v4l2_ctrl_handler_free(&itv->cxhdl.hdl);

	exit_ivtv_i2c(itv);

	free_irq(itv->pdev->irq, (void *)itv);
	ivtv_iounmap(itv);

	release_mem_region(itv->base_addr, IVTV_ENCODER_SIZE);
	release_mem_region(itv->base_addr + IVTV_REG_OFFSET, IVTV_REG_SIZE);
	if (itv->has_cx23415)
		release_mem_region(itv->base_addr + IVTV_DECODER_OFFSET, IVTV_DECODER_SIZE);

	pci_disable_device(itv->pdev);
	for (i = 0; i < IVTV_VBI_FRAMES; i++)
		kfree(itv->vbi.sliced_mpeg_data[i]);

	pr_info("Removed %s\n", itv->card_name);

	v4l2_device_unregister(&itv->v4l2_dev);
	kfree(itv);
}
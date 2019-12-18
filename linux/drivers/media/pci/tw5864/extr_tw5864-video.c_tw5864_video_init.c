#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dma_addr; void* addr; } ;
struct TYPE_6__ {int dma_addr; void* addr; } ;
struct tw5864_h264_frame {TYPE_3__ mv; TYPE_1__ vlc; } ;
struct tw5864_dev {size_t h264_buf_w_index; int irqmask; struct tw5864_h264_frame* h264_buf; TYPE_2__* pci; int /*<<< orphan*/  tasklet; TYPE_4__* inputs; int /*<<< orphan*/  slock; scalar_t__ h264_buf_r_index; scalar_t__ encoder_busy; } ;
struct TYPE_9__ {int nr; struct tw5864_dev* root; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int H264_BUF_CNT ; 
 int /*<<< orphan*/  H264_MV_BUF_SIZE ; 
 int /*<<< orphan*/  H264_VLC_BUF_SIZE ; 
 int TW5864_DI_EN ; 
 int /*<<< orphan*/  TW5864_ENC_BUF_PTR_REC1 ; 
 int /*<<< orphan*/  TW5864_FULL_HALF_MODE_SEL ; 
 int /*<<< orphan*/  TW5864_H264EN_BUS0_MAP ; 
 int /*<<< orphan*/  TW5864_H264EN_BUS1_MAP ; 
 int /*<<< orphan*/  TW5864_H264EN_BUS2_MAP ; 
 int /*<<< orphan*/  TW5864_H264EN_BUS3_MAP ; 
 int /*<<< orphan*/  TW5864_H264EN_CH_EN ; 
 int /*<<< orphan*/  TW5864_INDIR_CLK0_SEL ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRA_DLL_CLK90_SEL ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRA_DLL_DQS_SEL0 ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRA_DLL_DQS_SEL1 ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRB_DLL_CLK90_SEL ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRB_DLL_DQS_SEL0 ; 
 int /*<<< orphan*/  TW5864_INDIR_DDRB_DLL_DQS_SEL1 ; 
 int /*<<< orphan*/  TW5864_INDIR_PV_VD_CK_POL ; 
 int TW5864_INDIR_PV_VD_CK_POL_VD (int) ; 
 int /*<<< orphan*/  TW5864_INDIR_RESET ; 
 int TW5864_INDIR_RESET_DLL ; 
 int TW5864_INDIR_RESET_MUX_CORE ; 
 int TW5864_INDIR_RESET_VD ; 
 int /*<<< orphan*/  TW5864_INDIR_VD_108_POL ; 
 int TW5864_INDIR_VD_108_POL_BOTH ; 
 int TW5864_INPUTS ; 
 int /*<<< orphan*/  TW5864_INTERLACING ; 
 int TW5864_INTR_TIMER ; 
 int TW5864_INTR_VLC_DONE ; 
 int /*<<< orphan*/  TW5864_MASTER_ENB_REG ; 
 int TW5864_MVD_VLC_MAST_ENB ; 
 int /*<<< orphan*/  TW5864_MV_STREAM_BASE_ADDR ; 
 int /*<<< orphan*/  TW5864_PCI_INTR_CTL ; 
 int /*<<< orphan*/  TW5864_PCI_INTTM_SCALE ; 
 int TW5864_PCI_MAST_ENB ; 
 int TW5864_PCI_VLC_INTR_ENB ; 
 int /*<<< orphan*/  TW5864_SEN_EN_CH ; 
 int TW5864_TIMER_INTR_ENB ; 
 int /*<<< orphan*/  TW5864_VLC_STREAM_BASE_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw5864_encoder_tables_upload (struct tw5864_dev*) ; 
 int /*<<< orphan*/  tw5864_handle_frame_task ; 
 int /*<<< orphan*/  tw5864_irqmask_apply (struct tw5864_dev*) ; 
 int /*<<< orphan*/  tw5864_video_input_fini (TYPE_4__*) ; 
 int tw5864_video_input_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tw_indir_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

int tw5864_video_init(struct tw5864_dev *dev, int *video_nr)
{
	int i;
	int ret;
	unsigned long flags;
	int last_dma_allocated = -1;
	int last_input_nr_registered = -1;

	for (i = 0; i < H264_BUF_CNT; i++) {
		struct tw5864_h264_frame *frame = &dev->h264_buf[i];

		frame->vlc.addr = dma_alloc_coherent(&dev->pci->dev,
						     H264_VLC_BUF_SIZE,
						     &frame->vlc.dma_addr,
						     GFP_KERNEL | GFP_DMA32);
		if (!frame->vlc.addr) {
			dev_err(&dev->pci->dev, "dma alloc fail\n");
			ret = -ENOMEM;
			goto free_dma;
		}
		frame->mv.addr = dma_alloc_coherent(&dev->pci->dev,
						    H264_MV_BUF_SIZE,
						    &frame->mv.dma_addr,
						    GFP_KERNEL | GFP_DMA32);
		if (!frame->mv.addr) {
			dev_err(&dev->pci->dev, "dma alloc fail\n");
			ret = -ENOMEM;
			dma_free_coherent(&dev->pci->dev, H264_VLC_BUF_SIZE,
					  frame->vlc.addr, frame->vlc.dma_addr);
			goto free_dma;
		}
		last_dma_allocated = i;
	}

	tw5864_encoder_tables_upload(dev);

	/* Picture is distorted without this block */
	/* use falling edge to sample 54M to 108M */
	tw_indir_writeb(TW5864_INDIR_VD_108_POL, TW5864_INDIR_VD_108_POL_BOTH);
	tw_indir_writeb(TW5864_INDIR_CLK0_SEL, 0x00);

	tw_indir_writeb(TW5864_INDIR_DDRA_DLL_DQS_SEL0, 0x02);
	tw_indir_writeb(TW5864_INDIR_DDRA_DLL_DQS_SEL1, 0x02);
	tw_indir_writeb(TW5864_INDIR_DDRA_DLL_CLK90_SEL, 0x02);
	tw_indir_writeb(TW5864_INDIR_DDRB_DLL_DQS_SEL0, 0x02);
	tw_indir_writeb(TW5864_INDIR_DDRB_DLL_DQS_SEL1, 0x02);
	tw_indir_writeb(TW5864_INDIR_DDRB_DLL_CLK90_SEL, 0x02);

	/* video input reset */
	tw_indir_writeb(TW5864_INDIR_RESET, 0);
	tw_indir_writeb(TW5864_INDIR_RESET, TW5864_INDIR_RESET_VD |
			TW5864_INDIR_RESET_DLL | TW5864_INDIR_RESET_MUX_CORE);
	msleep(20);

	/*
	 * Select Part A mode for all channels.
	 * tw_setl instead of tw_clearl for Part B mode.
	 *
	 * I guess "Part B" is primarily for downscaled version of same channel
	 * which goes in Part A of same bus
	 */
	tw_writel(TW5864_FULL_HALF_MODE_SEL, 0);

	tw_indir_writeb(TW5864_INDIR_PV_VD_CK_POL,
			TW5864_INDIR_PV_VD_CK_POL_VD(0) |
			TW5864_INDIR_PV_VD_CK_POL_VD(1) |
			TW5864_INDIR_PV_VD_CK_POL_VD(2) |
			TW5864_INDIR_PV_VD_CK_POL_VD(3));

	spin_lock_irqsave(&dev->slock, flags);
	dev->encoder_busy = 0;
	dev->h264_buf_r_index = 0;
	dev->h264_buf_w_index = 0;
	tw_writel(TW5864_VLC_STREAM_BASE_ADDR,
		  dev->h264_buf[dev->h264_buf_w_index].vlc.dma_addr);
	tw_writel(TW5864_MV_STREAM_BASE_ADDR,
		  dev->h264_buf[dev->h264_buf_w_index].mv.dma_addr);
	spin_unlock_irqrestore(&dev->slock, flags);

	tw_writel(TW5864_SEN_EN_CH, 0x000f);
	tw_writel(TW5864_H264EN_CH_EN, 0x000f);

	tw_writel(TW5864_H264EN_BUS0_MAP, 0x00000000);
	tw_writel(TW5864_H264EN_BUS1_MAP, 0x00001111);
	tw_writel(TW5864_H264EN_BUS2_MAP, 0x00002222);
	tw_writel(TW5864_H264EN_BUS3_MAP, 0x00003333);

	/*
	 * Quote from Intersil (manufacturer):
	 * 0x0038 is managed by HW, and by default it won't pass the pointer set
	 * at 0x0010. So if you don't do encoding, 0x0038 should stay at '3'
	 * (with 4 frames in buffer). If you encode one frame and then move
	 * 0x0010 to '1' for example, HW will take one more frame and set it to
	 * buffer #0, and then you should see 0x0038 is set to '0'.  There is
	 * only one HW encoder engine, so 4 channels cannot get encoded
	 * simultaneously. But each channel does have its own buffer (for
	 * original frames and reconstructed frames). So there is no problem to
	 * manage encoding for 4 channels at same time and no need to force
	 * I-frames in switching channels.
	 * End of quote.
	 *
	 * If we set 0x0010 (TW5864_ENC_BUF_PTR_REC1) to 0 (for any channel), we
	 * have no "rolling" (until we change this value).
	 * If we set 0x0010 (TW5864_ENC_BUF_PTR_REC1) to 0x3, it starts to roll
	 * continuously together with 0x0038.
	 */
	tw_writel(TW5864_ENC_BUF_PTR_REC1, 0x00ff);
	tw_writel(TW5864_PCI_INTTM_SCALE, 0);

	tw_writel(TW5864_INTERLACING, TW5864_DI_EN);
	tw_writel(TW5864_MASTER_ENB_REG, TW5864_PCI_VLC_INTR_ENB);
	tw_writel(TW5864_PCI_INTR_CTL,
		  TW5864_TIMER_INTR_ENB | TW5864_PCI_MAST_ENB |
		  TW5864_MVD_VLC_MAST_ENB);

	dev->irqmask |= TW5864_INTR_VLC_DONE | TW5864_INTR_TIMER;
	tw5864_irqmask_apply(dev);

	tasklet_init(&dev->tasklet, tw5864_handle_frame_task,
		     (unsigned long)dev);

	for (i = 0; i < TW5864_INPUTS; i++) {
		dev->inputs[i].root = dev;
		dev->inputs[i].nr = i;
		ret = tw5864_video_input_init(&dev->inputs[i], video_nr[i]);
		if (ret)
			goto fini_video_inputs;
		last_input_nr_registered = i;
	}

	return 0;

fini_video_inputs:
	for (i = last_input_nr_registered; i >= 0; i--)
		tw5864_video_input_fini(&dev->inputs[i]);

	tasklet_kill(&dev->tasklet);

free_dma:
	for (i = last_dma_allocated; i >= 0; i--) {
		dma_free_coherent(&dev->pci->dev, H264_VLC_BUF_SIZE,
				  dev->h264_buf[i].vlc.addr,
				  dev->h264_buf[i].vlc.dma_addr);
		dma_free_coherent(&dev->pci->dev, H264_MV_BUF_SIZE,
				  dev->h264_buf[i].mv.addr,
				  dev->h264_buf[i].mv.dma_addr);
	}

	return ret;
}
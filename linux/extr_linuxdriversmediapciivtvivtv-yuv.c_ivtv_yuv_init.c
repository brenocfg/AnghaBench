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
struct yuv_playback_info {int reg_2834; int reg_2838; int reg_283c; int reg_2840; int reg_2844; int reg_2848; int reg_2854; int reg_285c; int reg_2864; int reg_2870; int reg_2874; int reg_2898; int reg_2890; int reg_289c; int reg_2918; int reg_291c; int reg_2920; int reg_2924; int reg_2928; int reg_292c; int reg_2930; int reg_2934; int reg_2938; int reg_293c; int reg_2940; int reg_2944; int reg_2948; int reg_294c; int reg_2950; int reg_2954; int reg_2958; int reg_295c; int reg_2960; int reg_2964; int reg_2968; int reg_296c; int reg_2970; int v_filter_1; int v_filter_2; int h_filter; int osd_x_offset; int osd_y_offset; int decode_height; int osd_vis_w; int osd_vis_h; int /*<<< orphan*/  next_dma_frame; scalar_t__ blanking_dmaptr; scalar_t__ blanking_ptr; } ;
struct ivtv {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/  osd_info; struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IVTV_DEBUG_WARN (char*,...) ; 
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_DECODING_YUV ; 
 int /*<<< orphan*/  IVTV_REG_VDM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kzalloc (int,int) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int read_reg (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg_sync (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivtv_yuv_init(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;

	IVTV_DEBUG_YUV("ivtv_yuv_init\n");

	/* Take a snapshot of the current register settings */
	yi->reg_2834 = read_reg(0x02834);
	yi->reg_2838 = read_reg(0x02838);
	yi->reg_283c = read_reg(0x0283c);
	yi->reg_2840 = read_reg(0x02840);
	yi->reg_2844 = read_reg(0x02844);
	yi->reg_2848 = read_reg(0x02848);
	yi->reg_2854 = read_reg(0x02854);
	yi->reg_285c = read_reg(0x0285c);
	yi->reg_2864 = read_reg(0x02864);
	yi->reg_2870 = read_reg(0x02870);
	yi->reg_2874 = read_reg(0x02874);
	yi->reg_2898 = read_reg(0x02898);
	yi->reg_2890 = read_reg(0x02890);

	yi->reg_289c = read_reg(0x0289c);
	yi->reg_2918 = read_reg(0x02918);
	yi->reg_291c = read_reg(0x0291c);
	yi->reg_2920 = read_reg(0x02920);
	yi->reg_2924 = read_reg(0x02924);
	yi->reg_2928 = read_reg(0x02928);
	yi->reg_292c = read_reg(0x0292c);
	yi->reg_2930 = read_reg(0x02930);
	yi->reg_2934 = read_reg(0x02934);
	yi->reg_2938 = read_reg(0x02938);
	yi->reg_293c = read_reg(0x0293c);
	yi->reg_2940 = read_reg(0x02940);
	yi->reg_2944 = read_reg(0x02944);
	yi->reg_2948 = read_reg(0x02948);
	yi->reg_294c = read_reg(0x0294c);
	yi->reg_2950 = read_reg(0x02950);
	yi->reg_2954 = read_reg(0x02954);
	yi->reg_2958 = read_reg(0x02958);
	yi->reg_295c = read_reg(0x0295c);
	yi->reg_2960 = read_reg(0x02960);
	yi->reg_2964 = read_reg(0x02964);
	yi->reg_2968 = read_reg(0x02968);
	yi->reg_296c = read_reg(0x0296c);
	yi->reg_2970 = read_reg(0x02970);

	yi->v_filter_1 = -1;
	yi->v_filter_2 = -1;
	yi->h_filter = -1;

	/* Set some valid size info */
	yi->osd_x_offset = read_reg(0x02a04) & 0x00000FFF;
	yi->osd_y_offset = (read_reg(0x02a04) >> 16) & 0x00000FFF;

	/* Bit 2 of reg 2878 indicates current decoder output format
	   0 : NTSC    1 : PAL */
	if (read_reg(0x2878) & 4)
		yi->decode_height = 576;
	else
		yi->decode_height = 480;

	if (!itv->osd_info) {
		yi->osd_vis_w = 720 - yi->osd_x_offset;
		yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
	} else {
		/* If no visible size set, assume full size */
		if (!yi->osd_vis_w)
			yi->osd_vis_w = 720 - yi->osd_x_offset;

		if (!yi->osd_vis_h) {
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		} else if (yi->osd_vis_h + yi->osd_y_offset > yi->decode_height) {
			/* If output video standard has changed, requested height may
			   not be legal */
			IVTV_DEBUG_WARN("Clipping yuv output - fb size (%d) exceeds video standard limit (%d)\n",
					yi->osd_vis_h + yi->osd_y_offset,
					yi->decode_height);
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		}
	}

	/* We need a buffer for blanking when Y plane is offset - non-fatal if we can't get one */
	yi->blanking_ptr = kzalloc(720 * 16, GFP_KERNEL|__GFP_NOWARN);
	if (yi->blanking_ptr) {
		yi->blanking_dmaptr = pci_map_single(itv->pdev, yi->blanking_ptr, 720*16, PCI_DMA_TODEVICE);
	} else {
		yi->blanking_dmaptr = 0;
		IVTV_DEBUG_WARN("Failed to allocate yuv blanking buffer\n");
	}

	/* Enable YUV decoder output */
	write_reg_sync(0x01, IVTV_REG_VDM);

	set_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags);
	atomic_set(&yi->next_dma_frame, 0);
}
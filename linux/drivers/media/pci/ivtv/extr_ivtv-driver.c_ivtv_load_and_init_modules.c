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
typedef  int u32 ;
struct TYPE_5__ {int raw_decoder_line_size; int raw_decoder_sav_odd_field; int raw_decoder_sav_even_field; int sliced_decoder_line_size; int sliced_decoder_sav_odd_field; int sliced_decoder_sav_even_field; } ;
struct ivtv {int hw_flags; int v4l2_cap; TYPE_2__ vbi; TYPE_3__* sd_video; TYPE_1__* card; void* sd_muxer; void* sd_audio; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int hw_all; int hw_audio_ctrl; int hw_muxer; scalar_t__ type; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ IVTV_CARD_CX23416GYC ; 
 int /*<<< orphan*/  IVTV_CARD_CX23416GYC_NOGR ; 
 int /*<<< orphan*/  IVTV_CARD_CX23416GYC_NOGRYCS ; 
 scalar_t__ IVTV_CARD_GV_MVPRX ; 
 scalar_t__ IVTV_CARD_GV_MVPRX2E ; 
 int IVTV_HW_CX25840 ; 
 int IVTV_HW_GPIO ; 
 int IVTV_HW_IR_ANY ; 
 int IVTV_HW_SAA7114 ; 
 int IVTV_HW_SAA7115 ; 
 int IVTV_HW_SAA711X ; 
 int IVTV_HW_SAA717X ; 
 int IVTV_HW_TVEEPROM ; 
 int IVTV_HW_UPD64031A ; 
 int IVTV_HW_UPD6408X ; 
 int /*<<< orphan*/  SAA7115_FREQ_24_576_MHZ ; 
 int /*<<< orphan*/  SAA7115_FREQ_FL_UCGC ; 
 int V4L2_CAP_SLICED_VBI_CAPTURE ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 void* ivtv_find_hw (struct ivtv*,int) ; 
 void* ivtv_get_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivtv_i2c_new_ir_legacy (struct ivtv*) ; 
 scalar_t__ ivtv_i2c_register (struct ivtv*,unsigned int) ; 
 int /*<<< orphan*/  s_crystal_freq ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void ivtv_load_and_init_modules(struct ivtv *itv)
{
	u32 hw = itv->card->hw_all;
	unsigned i;

	/* check which i2c devices are actually found */
	for (i = 0; i < 32; i++) {
		u32 device = BIT(i);

		if (!(device & hw))
			continue;
		if (device == IVTV_HW_GPIO || device == IVTV_HW_TVEEPROM) {
			/* GPIO and TVEEPROM do not use i2c probing */
			itv->hw_flags |= device;
			continue;
		}
		if (ivtv_i2c_register(itv, i) == 0)
			itv->hw_flags |= device;
	}

	/* probe for legacy IR controllers that aren't in card definitions */
	if ((itv->hw_flags & IVTV_HW_IR_ANY) == 0)
		ivtv_i2c_new_ir_legacy(itv);

	if (itv->card->hw_all & IVTV_HW_CX25840)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_CX25840);
	else if (itv->card->hw_all & IVTV_HW_SAA717X)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA717X);
	else if (itv->card->hw_all & IVTV_HW_SAA7114)
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA7114);
	else
		itv->sd_video = ivtv_find_hw(itv, IVTV_HW_SAA7115);
	itv->sd_audio = ivtv_find_hw(itv, itv->card->hw_audio_ctrl);
	itv->sd_muxer = ivtv_find_hw(itv, itv->card->hw_muxer);

	hw = itv->hw_flags;

	if (itv->card->type == IVTV_CARD_CX23416GYC) {
		/* Several variations of this card exist, detect which card
		   type should be used. */
		if ((hw & (IVTV_HW_UPD64031A | IVTV_HW_UPD6408X)) == 0)
			itv->card = ivtv_get_card(IVTV_CARD_CX23416GYC_NOGRYCS);
		else if ((hw & IVTV_HW_UPD64031A) == 0)
			itv->card = ivtv_get_card(IVTV_CARD_CX23416GYC_NOGR);
	}
	else if (itv->card->type == IVTV_CARD_GV_MVPRX ||
		 itv->card->type == IVTV_CARD_GV_MVPRX2E) {
		/* The crystal frequency of GVMVPRX is 24.576MHz */
		v4l2_subdev_call(itv->sd_video, video, s_crystal_freq,
			SAA7115_FREQ_24_576_MHZ, SAA7115_FREQ_FL_UCGC);
	}

	if (hw & IVTV_HW_CX25840) {
		itv->vbi.raw_decoder_line_size = 1444;
		itv->vbi.raw_decoder_sav_odd_field = 0x20;
		itv->vbi.raw_decoder_sav_even_field = 0x60;
		itv->vbi.sliced_decoder_line_size = 272;
		itv->vbi.sliced_decoder_sav_odd_field = 0xB0;
		itv->vbi.sliced_decoder_sav_even_field = 0xF0;
	}

	if (hw & IVTV_HW_SAA711X) {
		/* determine the exact saa711x model */
		itv->hw_flags &= ~IVTV_HW_SAA711X;

		if (strstr(itv->sd_video->name, "saa7114")) {
			itv->hw_flags |= IVTV_HW_SAA7114;
			/* VBI is not yet supported by the saa7114 driver. */
			itv->v4l2_cap &= ~(V4L2_CAP_SLICED_VBI_CAPTURE|V4L2_CAP_VBI_CAPTURE);
		} else {
			itv->hw_flags |= IVTV_HW_SAA7115;
		}
		itv->vbi.raw_decoder_line_size = 1443;
		itv->vbi.raw_decoder_sav_odd_field = 0x25;
		itv->vbi.raw_decoder_sav_even_field = 0x62;
		itv->vbi.sliced_decoder_line_size = 51;
		itv->vbi.sliced_decoder_sav_odd_field = 0xAB;
		itv->vbi.sliced_decoder_sav_even_field = 0xEC;
	}

	if (hw & IVTV_HW_SAA717X) {
		itv->vbi.raw_decoder_line_size = 1443;
		itv->vbi.raw_decoder_sav_odd_field = 0x25;
		itv->vbi.raw_decoder_sav_even_field = 0x62;
		itv->vbi.sliced_decoder_line_size = 51;
		itv->vbi.sliced_decoder_sav_odd_field = 0xAB;
		itv->vbi.sliced_decoder_sav_even_field = 0xEC;
	}
}
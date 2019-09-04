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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_hdmi {int dummy; } ;
typedef  enum hdmi_audio_sample_size { ____Placeholder_hdmi_audio_sample_size } hdmi_audio_sample_size ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_16BIT ; 
 int /*<<< orphan*/  AOUT_20BIT ; 
 int /*<<< orphan*/  AOUT_24BIT ; 
 int /*<<< orphan*/  AOUT_BNUM_SEL_MASK ; 
 int /*<<< orphan*/  GRL_AOUT_CFG ; 
#define  HDMI_AUDIO_SAMPLE_SIZE_16 131 
#define  HDMI_AUDIO_SAMPLE_SIZE_20 130 
#define  HDMI_AUDIO_SAMPLE_SIZE_24 129 
#define  HDMI_AUDIO_SAMPLE_SIZE_STREAM 128 
 int /*<<< orphan*/  mtk_hdmi_mask (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_bit_num(struct mtk_hdmi *hdmi,
					enum hdmi_audio_sample_size bit_num)
{
	u32 val;

	switch (bit_num) {
	case HDMI_AUDIO_SAMPLE_SIZE_16:
		val = AOUT_16BIT;
		break;
	case HDMI_AUDIO_SAMPLE_SIZE_20:
		val = AOUT_20BIT;
		break;
	case HDMI_AUDIO_SAMPLE_SIZE_24:
	case HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		val = AOUT_24BIT;
		break;
	}

	mtk_hdmi_mask(hdmi, GRL_AOUT_CFG, val, AOUT_BNUM_SEL_MASK);
}
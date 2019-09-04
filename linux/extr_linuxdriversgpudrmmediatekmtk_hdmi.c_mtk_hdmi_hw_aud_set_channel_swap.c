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
typedef  int /*<<< orphan*/  u8 ;
struct mtk_hdmi {int dummy; } ;
typedef  enum hdmi_aud_channel_swap_type { ____Placeholder_hdmi_aud_channel_swap_type } hdmi_aud_channel_swap_type ;

/* Variables and functions */
 int /*<<< orphan*/  GRL_CH_SWAP ; 
#define  HDMI_AUD_SWAP_LFE_CC 132 
#define  HDMI_AUD_SWAP_LR 131 
#define  HDMI_AUD_SWAP_LR_STATUS 130 
#define  HDMI_AUD_SWAP_LSRS 129 
#define  HDMI_AUD_SWAP_RLS_RRS 128 
 int /*<<< orphan*/  LFE_CC_SWAP ; 
 int /*<<< orphan*/  LR_STATUS_SWAP ; 
 int /*<<< orphan*/  LR_SWAP ; 
 int /*<<< orphan*/  LSRS_SWAP ; 
 int /*<<< orphan*/  RLS_RRS_SWAP ; 
 int /*<<< orphan*/  mtk_hdmi_mask (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_channel_swap(struct mtk_hdmi *hdmi,
					enum hdmi_aud_channel_swap_type swap)
{
	u8 swap_bit;

	switch (swap) {
	case HDMI_AUD_SWAP_LR:
		swap_bit = LR_SWAP;
		break;
	case HDMI_AUD_SWAP_LFE_CC:
		swap_bit = LFE_CC_SWAP;
		break;
	case HDMI_AUD_SWAP_LSRS:
		swap_bit = LSRS_SWAP;
		break;
	case HDMI_AUD_SWAP_RLS_RRS:
		swap_bit = RLS_RRS_SWAP;
		break;
	case HDMI_AUD_SWAP_LR_STATUS:
		swap_bit = LR_STATUS_SWAP;
		break;
	default:
		swap_bit = LFE_CC_SWAP;
		break;
	}
	mtk_hdmi_mask(hdmi, GRL_CH_SWAP, swap_bit, 0xff);
}
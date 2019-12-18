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
typedef  enum hdmi_aud_mclk { ____Placeholder_hdmi_aud_mclk } hdmi_aud_mclk ;

/* Variables and functions */
 int /*<<< orphan*/  CFG5_CD_RATIO_MASK ; 
 int /*<<< orphan*/  CFG5_FS128 ; 
 int /*<<< orphan*/  CFG5_FS256 ; 
 int /*<<< orphan*/  CFG5_FS384 ; 
 int /*<<< orphan*/  CFG5_FS512 ; 
 int /*<<< orphan*/  CFG5_FS768 ; 
 int /*<<< orphan*/  GRL_CFG5 ; 
#define  HDMI_AUD_MCLK_128FS 132 
#define  HDMI_AUD_MCLK_256FS 131 
#define  HDMI_AUD_MCLK_384FS 130 
#define  HDMI_AUD_MCLK_512FS 129 
#define  HDMI_AUD_MCLK_768FS 128 
 int /*<<< orphan*/  mtk_hdmi_read (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_mclk(struct mtk_hdmi *hdmi,
				     enum hdmi_aud_mclk mclk)
{
	u32 val;

	val = mtk_hdmi_read(hdmi, GRL_CFG5);
	val &= CFG5_CD_RATIO_MASK;

	switch (mclk) {
	case HDMI_AUD_MCLK_128FS:
		val |= CFG5_FS128;
		break;
	case HDMI_AUD_MCLK_256FS:
		val |= CFG5_FS256;
		break;
	case HDMI_AUD_MCLK_384FS:
		val |= CFG5_FS384;
		break;
	case HDMI_AUD_MCLK_512FS:
		val |= CFG5_FS512;
		break;
	case HDMI_AUD_MCLK_768FS:
		val |= CFG5_FS768;
		break;
	default:
		val |= CFG5_FS256;
		break;
	}
	mtk_hdmi_write(hdmi, GRL_CFG5, val);
}
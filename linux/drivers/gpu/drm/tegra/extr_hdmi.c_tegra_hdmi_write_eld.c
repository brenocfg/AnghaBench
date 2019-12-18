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
typedef  size_t u32 ;
struct TYPE_3__ {size_t* eld; } ;
struct TYPE_4__ {TYPE_1__ connector; } ;
struct tegra_hdmi {TYPE_2__ output; } ;

/* Variables and functions */
 size_t HDMI_ELD_BUFFER_SIZE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_AUDIO_HDA_PRESENSE ; 
 size_t SOR_AUDIO_HDA_PRESENSE_PRESENT ; 
 size_t SOR_AUDIO_HDA_PRESENSE_VALID ; 
 size_t drm_eld_size (size_t*) ; 
 int /*<<< orphan*/  tegra_hdmi_writel (struct tegra_hdmi*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_hdmi_write_eld(struct tegra_hdmi *hdmi)
{
	size_t length = drm_eld_size(hdmi->output.connector.eld), i;
	u32 value;

	for (i = 0; i < length; i++)
		tegra_hdmi_writel(hdmi, i << 8 | hdmi->output.connector.eld[i],
				  HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR);

	/*
	 * The HDA codec will always report an ELD buffer size of 96 bytes and
	 * the HDA codec driver will check that each byte read from the buffer
	 * is valid. Therefore every byte must be written, even if no 96 bytes
	 * were parsed from EDID.
	 */
	for (i = length; i < HDMI_ELD_BUFFER_SIZE; i++)
		tegra_hdmi_writel(hdmi, i << 8 | 0,
				  HDMI_NV_PDISP_SOR_AUDIO_HDA_ELD_BUFWR);

	value = SOR_AUDIO_HDA_PRESENSE_VALID | SOR_AUDIO_HDA_PRESENSE_PRESENT;
	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_SOR_AUDIO_HDA_PRESENSE);
}
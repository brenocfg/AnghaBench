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
struct tegra_hdmi_audio_config {int pclk; } ;

/* Variables and functions */
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_176_4k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_192k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_32k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_44_1k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_48k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_88_2k ; 
 struct tegra_hdmi_audio_config* tegra_hdmi_audio_96k ; 

__attribute__((used)) static const struct tegra_hdmi_audio_config *
tegra_hdmi_get_audio_config(unsigned int sample_rate, unsigned int pclk)
{
	const struct tegra_hdmi_audio_config *table;

	switch (sample_rate) {
	case 32000:
		table = tegra_hdmi_audio_32k;
		break;

	case 44100:
		table = tegra_hdmi_audio_44_1k;
		break;

	case 48000:
		table = tegra_hdmi_audio_48k;
		break;

	case 88200:
		table = tegra_hdmi_audio_88_2k;
		break;

	case 96000:
		table = tegra_hdmi_audio_96k;
		break;

	case 176400:
		table = tegra_hdmi_audio_176_4k;
		break;

	case 192000:
		table = tegra_hdmi_audio_192k;
		break;

	default:
		return NULL;
	}

	while (table->pclk) {
		if (table->pclk == pclk)
			return table;

		table++;
	}

	return NULL;
}
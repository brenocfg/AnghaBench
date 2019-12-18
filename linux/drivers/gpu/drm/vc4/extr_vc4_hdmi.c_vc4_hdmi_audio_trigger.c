#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  channels; } ;
struct vc4_hdmi {TYPE_1__ audio; struct drm_encoder* encoder; } ;
struct vc4_dev {int dummy; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HD_WRITE (int /*<<< orphan*/ ,int) ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  VC4_HDMI_TX_PHY_CTL0 ; 
 int VC4_HDMI_TX_PHY_RNG_PWRDN ; 
 int /*<<< orphan*/  VC4_HD_MAI_CTL ; 
 int /*<<< orphan*/  VC4_HD_MAI_CTL_CHNUM ; 
 int VC4_HD_MAI_CTL_DLATE ; 
 int VC4_HD_MAI_CTL_ENABLE ; 
 int VC4_HD_MAI_CTL_ERRORE ; 
 int VC4_HD_MAI_CTL_ERRORF ; 
 int VC4_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_hdmi* dai_to_hdmi (struct snd_soc_dai*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_hdmi_set_audio_infoframe (struct drm_encoder*) ; 

__attribute__((used)) static int vc4_hdmi_audio_trigger(struct snd_pcm_substream *substream, int cmd,
				  struct snd_soc_dai *dai)
{
	struct vc4_hdmi *hdmi = dai_to_hdmi(dai);
	struct drm_encoder *encoder = hdmi->encoder;
	struct drm_device *drm = encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(drm);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		vc4_hdmi_set_audio_infoframe(encoder);
		HDMI_WRITE(VC4_HDMI_TX_PHY_CTL0,
			   HDMI_READ(VC4_HDMI_TX_PHY_CTL0) &
			   ~VC4_HDMI_TX_PHY_RNG_PWRDN);
		HD_WRITE(VC4_HD_MAI_CTL,
			 VC4_SET_FIELD(hdmi->audio.channels,
				       VC4_HD_MAI_CTL_CHNUM) |
			 VC4_HD_MAI_CTL_ENABLE);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		HD_WRITE(VC4_HD_MAI_CTL,
			 VC4_HD_MAI_CTL_DLATE |
			 VC4_HD_MAI_CTL_ERRORE |
			 VC4_HD_MAI_CTL_ERRORF);
		HDMI_WRITE(VC4_HDMI_TX_PHY_CTL0,
			   HDMI_READ(VC4_HDMI_TX_PHY_CTL0) |
			   VC4_HDMI_TX_PHY_RNG_PWRDN);
		break;
	default:
		break;
	}

	return 0;
}
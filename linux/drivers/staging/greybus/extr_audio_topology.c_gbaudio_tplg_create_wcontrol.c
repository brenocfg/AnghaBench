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
struct snd_kcontrol_new {int dummy; } ;
struct gbaudio_module_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct gb_audio_control {int iface; int /*<<< orphan*/  id; int /*<<< orphan*/  name; TYPE_1__ info; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED 129 
#define  SNDRV_CTL_ELEM_IFACE_MIXER 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gbaudio_tplg_create_enum_ctl (struct gbaudio_module_info*,struct snd_kcontrol_new*,struct gb_audio_control*) ; 
 int gbaudio_tplg_create_mixer_ctl (struct gbaudio_module_info*,struct snd_kcontrol_new*,struct gb_audio_control*) ; 

__attribute__((used)) static int gbaudio_tplg_create_wcontrol(struct gbaudio_module_info *gb,
					struct snd_kcontrol_new *kctl,
					struct gb_audio_control *ctl)
{
	int ret;

	switch (ctl->iface) {
	case SNDRV_CTL_ELEM_IFACE_MIXER:
		switch (ctl->info.type) {
		case GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
			ret = gbaudio_tplg_create_enum_ctl(gb, kctl, ctl);
			break;
		default:
			ret = gbaudio_tplg_create_mixer_ctl(gb, kctl, ctl);
			break;
		}
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(gb->dev, "%s:%d DAPM control created, ret:%d\n", ctl->name,
		ctl->id, ret);
	return ret;
}
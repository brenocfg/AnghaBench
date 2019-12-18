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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct bcm2835_chip {int volume; int mute; int dest; int /*<<< orphan*/  audio_mutex; TYPE_3__* card; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCM_PLAYBACK_DEVICE ; 
 scalar_t__ PCM_PLAYBACK_MUTE ; 
 scalar_t__ PCM_PLAYBACK_VOLUME ; 
 scalar_t__ bcm2835_audio_set_chip_ctls (struct bcm2835_chip*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm2835_chip* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_bcm2835_ctl_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);
	int val, *valp;
	int changed = 0;

	if (kcontrol->private_value == PCM_PLAYBACK_VOLUME)
		valp = &chip->volume;
	else if (kcontrol->private_value == PCM_PLAYBACK_MUTE)
		valp = &chip->mute;
	else if (kcontrol->private_value == PCM_PLAYBACK_DEVICE)
		valp = &chip->dest;
	else
		return -EINVAL;

	val = ucontrol->value.integer.value[0];
	mutex_lock(&chip->audio_mutex);
	if (val != *valp) {
		*valp = val;
		changed = 1;
		if (bcm2835_audio_set_chip_ctls(chip))
			dev_err(chip->card->dev, "Failed to set ALSA controls..\n");
	}
	mutex_unlock(&chip->audio_mutex);
	return changed;
}
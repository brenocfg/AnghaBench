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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct bcm2835_chip {int spdif_status; int /*<<< orphan*/  audio_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bcm2835_chip* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_bcm2835_spdif_default_get(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);
	int i;

	mutex_lock(&chip->audio_mutex);

	for (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] =
			(chip->spdif_status >> (i * 8)) & 0xff;

	mutex_unlock(&chip->audio_mutex);
	return 0;
}
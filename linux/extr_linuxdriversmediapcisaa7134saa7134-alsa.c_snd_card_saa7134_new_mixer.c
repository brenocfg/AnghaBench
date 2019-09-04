#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct TYPE_8__ {int /*<<< orphan*/  capture_source_addr; struct snd_kcontrol** capture_ctl; struct snd_card* card; } ;
typedef  TYPE_1__ snd_card_saa7134_t ;
struct TYPE_9__ {int private_value; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  MIXER_ADDR_UNSELECTED ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* snd_saa7134_capture_controls ; 
 TYPE_2__* snd_saa7134_volume_controls ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_card_saa7134_new_mixer(snd_card_saa7134_t * chip)
{
	struct snd_card *card = chip->card;
	struct snd_kcontrol *kcontrol;
	unsigned int idx;
	int err, addr;

	strcpy(card->mixername, "SAA7134 Mixer");

	for (idx = 0; idx < ARRAY_SIZE(snd_saa7134_volume_controls); idx++) {
		kcontrol = snd_ctl_new1(&snd_saa7134_volume_controls[idx],
					chip);
		err = snd_ctl_add(card, kcontrol);
		if (err < 0)
			return err;
	}

	for (idx = 0; idx < ARRAY_SIZE(snd_saa7134_capture_controls); idx++) {
		kcontrol = snd_ctl_new1(&snd_saa7134_capture_controls[idx],
					chip);
		addr = snd_saa7134_capture_controls[idx].private_value;
		chip->capture_ctl[addr] = kcontrol;
		err = snd_ctl_add(card, kcontrol);
		if (err < 0)
			return err;
	}

	chip->capture_source_addr = MIXER_ADDR_UNSELECTED;
	return 0;
}
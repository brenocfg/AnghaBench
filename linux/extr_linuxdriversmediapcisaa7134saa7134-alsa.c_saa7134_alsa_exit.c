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

/* Variables and functions */
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/ * saa7134_dmasound_exit ; 
 int /*<<< orphan*/ * saa7134_dmasound_init ; 
 int /*<<< orphan*/  snd_card_free (scalar_t__) ; 
 scalar_t__* snd_saa7134_cards ; 

__attribute__((used)) static void saa7134_alsa_exit(void)
{
	int idx;

	for (idx = 0; idx < SNDRV_CARDS; idx++) {
		if (snd_saa7134_cards[idx])
			snd_card_free(snd_saa7134_cards[idx]);
	}

	saa7134_dmasound_init = NULL;
	saa7134_dmasound_exit = NULL;
	pr_info("saa7134 ALSA driver for DMA sound unloaded\n");

	return;
}
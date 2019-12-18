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
struct tm6000_core {struct snd_tm6000_card* adev; } ;
struct snd_tm6000_card {int /*<<< orphan*/ * card; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_tm6000_card*) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tm6000_audio_fini(struct tm6000_core *dev)
{
	struct snd_tm6000_card *chip;

	if (!dev)
		return 0;
	chip = dev->adev;

	if (!chip)
		return 0;

	if (!chip->card)
		return 0;

	snd_card_free(chip->card);
	chip->card = NULL;
	kfree(chip);
	dev->adev = NULL;

	return 0;
}
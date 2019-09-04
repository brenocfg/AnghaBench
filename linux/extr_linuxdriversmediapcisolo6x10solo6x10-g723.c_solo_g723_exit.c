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
struct solo_dev {int /*<<< orphan*/ * snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_AUDIO_CONTROL ; 
 int /*<<< orphan*/  SOLO_IRQ_G723 ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void solo_g723_exit(struct solo_dev *solo_dev)
{
	if (!solo_dev->snd_card)
		return;

	solo_reg_write(solo_dev, SOLO_AUDIO_CONTROL, 0);
	solo_irq_off(solo_dev, SOLO_IRQ_G723);

	snd_card_free(solo_dev->snd_card);
	solo_dev->snd_card = NULL;
}
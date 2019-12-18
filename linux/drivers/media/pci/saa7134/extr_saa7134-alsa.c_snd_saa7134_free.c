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
struct snd_card {TYPE_2__* private_data; } ;
struct TYPE_5__ {scalar_t__ irq; TYPE_1__* dev; } ;
typedef  TYPE_2__ snd_card_saa7134_t ;
struct TYPE_6__ {int /*<<< orphan*/ * priv_data; } ;
struct TYPE_4__ {TYPE_3__ dmasound; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_3__*) ; 

__attribute__((used)) static void snd_saa7134_free(struct snd_card * card)
{
	snd_card_saa7134_t *chip = card->private_data;

	if (chip->dev->dmasound.priv_data == NULL)
		return;

	if (chip->irq >= 0)
		free_irq(chip->irq, &chip->dev->dmasound);

	chip->dev->dmasound.priv_data = NULL;

}
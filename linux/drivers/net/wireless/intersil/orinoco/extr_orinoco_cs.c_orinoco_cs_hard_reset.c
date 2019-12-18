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
struct pcmcia_device {int /*<<< orphan*/  socket; } ;
struct orinoco_private {struct orinoco_pccard* card; } ;
struct orinoco_pccard {int /*<<< orphan*/  hard_reset_in_progress; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pcmcia_reset_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
orinoco_cs_hard_reset(struct orinoco_private *priv)
{
	struct orinoco_pccard *card = priv->card;
	struct pcmcia_device *link = card->p_dev;
	int err;

	/* We need atomic ops here, because we're not holding the lock */
	set_bit(0, &card->hard_reset_in_progress);

	err = pcmcia_reset_card(link->socket);
	if (err)
		return err;

	msleep(100);
	clear_bit(0, &card->hard_reset_in_progress);

	return 0;
}
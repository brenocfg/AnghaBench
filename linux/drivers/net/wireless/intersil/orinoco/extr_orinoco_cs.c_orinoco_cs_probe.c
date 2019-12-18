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
struct pcmcia_device {struct orinoco_private* priv; int /*<<< orphan*/  dev; } ;
struct orinoco_private {struct orinoco_pccard* card; } ;
struct orinoco_pccard {struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct orinoco_private* alloc_orinocodev (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int orinoco_cs_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  orinoco_cs_hard_reset ; 

__attribute__((used)) static int
orinoco_cs_probe(struct pcmcia_device *link)
{
	struct orinoco_private *priv;
	struct orinoco_pccard *card;

	priv = alloc_orinocodev(sizeof(*card), &link->dev,
				orinoco_cs_hard_reset, NULL);
	if (!priv)
		return -ENOMEM;
	card = priv->card;

	/* Link both structures together */
	card->p_dev = link;
	link->priv = priv;

	return orinoco_cs_config(link);
}
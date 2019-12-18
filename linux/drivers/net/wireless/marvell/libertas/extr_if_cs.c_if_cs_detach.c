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
struct pcmcia_device {struct if_cs_card* priv; } ;
struct if_cs_card {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_cs_disable_ints (struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (struct if_cs_card*) ; 
 int /*<<< orphan*/  lbs_remove_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_stop_card (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void if_cs_detach(struct pcmcia_device *p_dev)
{
	struct if_cs_card *card = p_dev->priv;

	lbs_stop_card(card->priv);
	lbs_remove_card(card->priv);
	if_cs_disable_ints(card);
	if_cs_release(p_dev);
	kfree(card);
}
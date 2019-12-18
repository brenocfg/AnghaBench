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
struct pcmcia_device {struct orinoco_private* priv; } ;
struct orinoco_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_orinocodev (struct orinoco_private*) ; 
 int /*<<< orphan*/  orinoco_if_del (struct orinoco_private*) ; 
 int /*<<< orphan*/  spectrum_cs_release (struct pcmcia_device*) ; 

__attribute__((used)) static void spectrum_cs_detach(struct pcmcia_device *link)
{
	struct orinoco_private *priv = link->priv;

	orinoco_if_del(priv);

	spectrum_cs_release(link);

	free_orinocodev(priv);
}
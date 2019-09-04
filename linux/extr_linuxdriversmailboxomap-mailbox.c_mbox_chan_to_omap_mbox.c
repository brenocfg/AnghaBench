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
struct omap_mbox {int dummy; } ;
struct mbox_chan {scalar_t__ con_priv; } ;

/* Variables and functions */

__attribute__((used)) static struct omap_mbox *mbox_chan_to_omap_mbox(struct mbox_chan *chan)
{
	if (!chan || !chan->con_priv)
		return NULL;

	return (struct omap_mbox *)chan->con_priv;
}
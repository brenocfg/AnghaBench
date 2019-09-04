#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfar_private {int num_grps; int /*<<< orphan*/  ndev; TYPE_1__* gfargrp; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** irqinfo; } ;

/* Variables and functions */
 int GFAR_NUM_IRQS ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_gfar_dev(struct gfar_private *priv)
{
	int i, j;

	for (i = 0; i < priv->num_grps; i++)
		for (j = 0; j < GFAR_NUM_IRQS; j++) {
			kfree(priv->gfargrp[i].irqinfo[j]);
			priv->gfargrp[i].irqinfo[j] = NULL;
		}

	free_netdev(priv->ndev);
}
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
struct gfar_private {int num_grps; int /*<<< orphan*/ * gfargrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_grp_irqs (int /*<<< orphan*/ *) ; 
 int register_grp_irqs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfar_request_irq(struct gfar_private *priv)
{
	int err, i, j;

	for (i = 0; i < priv->num_grps; i++) {
		err = register_grp_irqs(&priv->gfargrp[i]);
		if (err) {
			for (j = 0; j < i; j++)
				free_grp_irqs(&priv->gfargrp[j]);
			return err;
		}
	}

	return 0;
}
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
struct rcar_du_group {scalar_t__ use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcar_du_group_setup (struct rcar_du_group*) ; 

int rcar_du_group_get(struct rcar_du_group *rgrp)
{
	if (rgrp->use_count)
		goto done;

	rcar_du_group_setup(rgrp);

done:
	rgrp->use_count++;
	return 0;
}
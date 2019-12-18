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
struct rcar_du_group {int need_restart; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rcar_du_group_start_stop (struct rcar_du_group*,int) ; 

void rcar_du_group_restart(struct rcar_du_group *rgrp)
{
	rgrp->need_restart = false;

	__rcar_du_group_start_stop(rgrp, false);
	__rcar_du_group_start_stop(rgrp, true);
}
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
struct rcar_du_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSYSR ; 
 int DSYSR_DEN ; 
 int DSYSR_DRES ; 
 int rcar_du_group_read (struct rcar_du_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __rcar_du_group_start_stop(struct rcar_du_group *rgrp, bool start)
{
	rcar_du_group_write(rgrp, DSYSR,
		(rcar_du_group_read(rgrp, DSYSR) & ~(DSYSR_DRES | DSYSR_DEN)) |
		(start ? DSYSR_DEN : DSYSR_DRES));
}
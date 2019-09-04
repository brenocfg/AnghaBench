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
typedef  scalar_t__ u32 ;
struct rcar_du_group {scalar_t__ mmio_offset; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ rcar_du_read (int /*<<< orphan*/ ,scalar_t__) ; 

u32 rcar_du_group_read(struct rcar_du_group *rgrp, u32 reg)
{
	return rcar_du_read(rgrp->dev, rgrp->mmio_offset + reg);
}
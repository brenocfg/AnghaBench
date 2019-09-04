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
 int /*<<< orphan*/  rcar_du_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void rcar_du_group_write(struct rcar_du_group *rgrp, u32 reg, u32 data)
{
	rcar_du_write(rgrp->dev, rgrp->mmio_offset + reg, data);
}
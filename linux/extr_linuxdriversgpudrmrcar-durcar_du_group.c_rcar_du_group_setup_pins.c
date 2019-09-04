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
typedef  int /*<<< orphan*/  u32 ;
struct rcar_du_group {int channels_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DEFR6 ; 
 int /*<<< orphan*/  DEFR6_CODE ; 
 int /*<<< orphan*/  DEFR6_ODPM02_DISP ; 
 int /*<<< orphan*/  DEFR6_ODPM12_DISP ; 
 int /*<<< orphan*/  rcar_du_group_write (struct rcar_du_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_group_setup_pins(struct rcar_du_group *rgrp)
{
	u32 defr6 = DEFR6_CODE;

	if (rgrp->channels_mask & BIT(0))
		defr6 |= DEFR6_ODPM02_DISP;

	if (rgrp->channels_mask & BIT(1))
		defr6 |= DEFR6_ODPM12_DISP;

	rcar_du_group_write(rgrp, DEFR6, defr6);
}
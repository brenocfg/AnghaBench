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
struct gfar_private {TYPE_1__* gfargrp; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int MAXGROUPS ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void unmap_group_regs(struct gfar_private *priv)
{
	int i;

	for (i = 0; i < MAXGROUPS; i++)
		if (priv->gfargrp[i].regs)
			iounmap(priv->gfargrp[i].regs);
}
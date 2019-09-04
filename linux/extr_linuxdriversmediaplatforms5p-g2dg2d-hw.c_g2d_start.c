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
struct g2d_dev {TYPE_1__* variant; } ;
struct TYPE_2__ {scalar_t__ hw_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITBLT_START_REG ; 
 int /*<<< orphan*/  CACHECTL_REG ; 
 int /*<<< orphan*/  INTEN_REG ; 
 scalar_t__ TYPE_G2D_3X ; 
 int /*<<< orphan*/  w (int,int /*<<< orphan*/ ) ; 

void g2d_start(struct g2d_dev *d)
{
	/* Clear cache */
	if (d->variant->hw_rev == TYPE_G2D_3X)
		w(0x7, CACHECTL_REG);

	/* Enable interrupt */
	w(1, INTEN_REG);
	/* Start G2D engine */
	w(1, BITBLT_START_REG);
}
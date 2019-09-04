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
struct gfar_priv_grp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ER ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gfar_priv_grp*) ; 
 TYPE_1__* gfar_irq (struct gfar_priv_grp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_grp_irqs(struct gfar_priv_grp *grp)
{
	free_irq(gfar_irq(grp, TX)->irq, grp);
	free_irq(gfar_irq(grp, RX)->irq, grp);
	free_irq(gfar_irq(grp, ER)->irq, grp);
}
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
struct wil6210_priv {int n_msi; TYPE_1__* pdev; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int) ; 

void wil_enable_irq(struct wil6210_priv *wil)
{
	int irq = wil->pdev->irq;

	enable_irq(irq);
	if (wil->n_msi == 3) {
		enable_irq(irq + 1);
		enable_irq(irq + 2);
	}
}
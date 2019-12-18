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
struct device {int /*<<< orphan*/  msi_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  msi_domain_free_irqs (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  ti_sci_inta_msi_free_descs (struct device*) ; 

void ti_sci_inta_msi_domain_free_irqs(struct device *dev)
{
	msi_domain_free_irqs(dev->msi_domain, dev);
	ti_sci_inta_msi_free_descs(dev);
}
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
struct st_nci_i2c_phy {int irq_active; TYPE_1__* i2c_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_nci_i2c_disable(void *phy_id)
{
	struct st_nci_i2c_phy *phy = phy_id;

	disable_irq_nosync(phy->i2c_dev->irq);
	phy->irq_active = false;
}
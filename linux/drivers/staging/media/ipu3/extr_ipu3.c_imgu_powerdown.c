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
struct imgu_device {int /*<<< orphan*/  base; TYPE_1__* pci_dev; int /*<<< orphan*/  mmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  imgu_css_set_powerdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_mmu_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imgu_powerdown(struct imgu_device *imgu)
{
	imgu_mmu_suspend(imgu->mmu);
	imgu_css_set_powerdown(&imgu->pci_dev->dev, imgu->base);
}
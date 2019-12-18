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
struct imgu_device {int /*<<< orphan*/  mmu; int /*<<< orphan*/  base; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int imgu_css_set_powerup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_mmu_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imgu_powerup(struct imgu_device *imgu)
{
	int r;

	r = imgu_css_set_powerup(&imgu->pci_dev->dev, imgu->base);
	if (r)
		return r;

	imgu_mmu_resume(imgu->mmu);
	return 0;
}
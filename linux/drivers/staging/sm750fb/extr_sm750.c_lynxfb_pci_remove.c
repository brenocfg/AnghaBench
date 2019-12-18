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
struct TYPE_2__ {int /*<<< orphan*/  vram; } ;
struct sm750_dev {int /*<<< orphan*/  pvMem; int /*<<< orphan*/  pvReg; TYPE_1__ mtrr; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_settings ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct sm750_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  sm750fb_framebuffer_release (struct sm750_dev*) ; 

__attribute__((used)) static void lynxfb_pci_remove(struct pci_dev *pdev)
{
	struct sm750_dev *sm750_dev;

	sm750_dev = pci_get_drvdata(pdev);

	sm750fb_framebuffer_release(sm750_dev);
	arch_phys_wc_del(sm750_dev->mtrr.vram);

	iounmap(sm750_dev->pvReg);
	iounmap(sm750_dev->pvMem);
	kfree(g_settings);
}
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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfad_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_EEH_BUSY ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  bfad_rport_online_wait (struct bfad_s*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct bfad_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bfad_pci_resume(struct pci_dev *pdev)
{
	unsigned long	flags;
	struct bfad_s *bfad = pci_get_drvdata(pdev);

	dev_printk(KERN_WARNING, &pdev->dev, "resume\n");

	/* wait until the link is online */
	bfad_rport_online_wait(bfad);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfad->bfad_flags &= ~BFAD_EEH_BUSY;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
}
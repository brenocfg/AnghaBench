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
struct sym_data {scalar_t__ io_reset; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 struct sym_data* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym2_io_resume(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct sym_data *sym_data = shost_priv(shost);

	spin_lock_irq(shost->host_lock);
	if (sym_data->io_reset)
		complete(sym_data->io_reset);
	spin_unlock_irq(shost->host_lock);
}
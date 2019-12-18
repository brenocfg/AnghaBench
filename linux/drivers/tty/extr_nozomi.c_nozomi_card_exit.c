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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct nozomi {int index_start; int /*<<< orphan*/  base_addr; struct nozomi* send_buf; TYPE_1__* port; int /*<<< orphan*/  reg_fcr; int /*<<< orphan*/  reg_ier; scalar_t__ last_ier; } ;
struct ctrl_ul {int port; int DTR; scalar_t__ RTS; scalar_t__ reserved; } ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_ul; int /*<<< orphan*/ * ul_addr; } ;

/* Variables and functions */
 scalar_t__ CTRL_UL ; 
 int /*<<< orphan*/  DBG1 (char*,int /*<<< orphan*/ ) ; 
 int MAX_PORT ; 
 size_t PORT_CTRL ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nozomi*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nozomi*) ; 
 int /*<<< orphan*/ ** ndevs ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct nozomi* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  remove_sysfs_files (struct nozomi*) ; 
 int /*<<< orphan*/  tty_exit (struct nozomi*) ; 
 int /*<<< orphan*/  write_mem32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writew (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nozomi_card_exit(struct pci_dev *pdev)
{
	int i;
	struct ctrl_ul ctrl;
	struct nozomi *dc = pci_get_drvdata(pdev);

	/* Disable all interrupts */
	dc->last_ier = 0;
	writew(dc->last_ier, dc->reg_ier);

	tty_exit(dc);

	/* Send 0x0001, command card to resend the reset token.  */
	/* This is to get the reset when the module is reloaded. */
	ctrl.port = 0x00;
	ctrl.reserved = 0;
	ctrl.RTS = 0;
	ctrl.DTR = 1;
	DBG1("sending flow control 0x%04X", *((u16 *)&ctrl));

	/* Setup dc->reg addresses to we can use defines here */
	write_mem32(dc->port[PORT_CTRL].ul_addr[0], (u32 *)&ctrl, 2);
	writew(CTRL_UL, dc->reg_fcr);	/* push the token to the card. */

	remove_sysfs_files(dc);

	free_irq(pdev->irq, dc);

	for (i = 0; i < MAX_PORT; i++)
		kfifo_free(&dc->port[i].fifo_ul);

	kfree(dc->send_buf);

	iounmap(dc->base_addr);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	ndevs[dc->index_start / MAX_PORT] = NULL;

	kfree(dc);
}
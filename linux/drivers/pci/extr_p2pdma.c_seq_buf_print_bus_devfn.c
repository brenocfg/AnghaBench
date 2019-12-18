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
struct seq_buf {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  seq_buf_printf (struct seq_buf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seq_buf_print_bus_devfn(struct seq_buf *buf, struct pci_dev *pdev)
{
	if (!buf)
		return;

	seq_buf_printf(buf, "%s;", pci_name(pdev));
}
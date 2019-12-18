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
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

ssize_t pci_p2pdma_enable_show(char *page, struct pci_dev *p2p_dev,
			       bool use_p2pdma)
{
	if (!use_p2pdma)
		return sprintf(page, "0\n");

	if (!p2p_dev)
		return sprintf(page, "1\n");

	return sprintf(page, "%s\n", pci_name(p2p_dev));
}
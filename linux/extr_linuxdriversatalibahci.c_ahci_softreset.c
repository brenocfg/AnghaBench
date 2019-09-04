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
struct ata_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ahci_check_ready ; 
 int ahci_do_softreset (struct ata_link*,unsigned int*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int sata_srst_pmp (struct ata_link*) ; 

__attribute__((used)) static int ahci_softreset(struct ata_link *link, unsigned int *class,
			  unsigned long deadline)
{
	int pmp = sata_srst_pmp(link);

	DPRINTK("ENTER\n");

	return ahci_do_softreset(link, class, pmp, deadline, ahci_check_ready);
}
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

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ce4100_reset(struct pci_dev *dev)
{
	int i;

	for (i = 0; i < 10; i++) {
		outb(0x2, 0xcf9);
		udelay(50);
	}
}
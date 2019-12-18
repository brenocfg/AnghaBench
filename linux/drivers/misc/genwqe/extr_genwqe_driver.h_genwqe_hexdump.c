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
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  GENWQE_DEVNAME ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,void const*,unsigned int,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void genwqe_hexdump(struct pci_dev *pci_dev,
				  const void *buff, unsigned int size)
{
	char prefix[32];

	scnprintf(prefix, sizeof(prefix), "%s %s: ",
		  GENWQE_DEVNAME, pci_name(pci_dev));

	print_hex_dump_debug(prefix, DUMP_PREFIX_OFFSET, 16, 1, buff,
			     size, true);
}
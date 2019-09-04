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

/* Variables and functions */
 int /*<<< orphan*/  NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int superio_inb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_outb (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nct6791_enable_io_mapping(int sioaddr)
{
	int val;

	val = superio_inb(sioaddr, NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE);
	if (val & 0x10) {
		pr_info("Enabling hardware monitor logical device mappings.\n");
		superio_outb(sioaddr, NCT6791_REG_HM_IO_SPACE_LOCK_ENABLE,
			     val & ~0x10);
	}
}
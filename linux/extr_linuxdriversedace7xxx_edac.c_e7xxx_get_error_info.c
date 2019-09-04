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
struct mem_ctl_info {scalar_t__ pvt_info; } ;
struct e7xxx_pvt {int /*<<< orphan*/  bridge_ck; } ;
struct e7xxx_error_info {int dram_ferr; int dram_nerr; int /*<<< orphan*/  dram_uelog_add; int /*<<< orphan*/  dram_celog_syndrome; int /*<<< orphan*/  dram_celog_add; } ;

/* Variables and functions */
 int /*<<< orphan*/  E7XXX_DRAM_CELOG_ADD ; 
 int /*<<< orphan*/  E7XXX_DRAM_CELOG_SYNDROME ; 
 int /*<<< orphan*/  E7XXX_DRAM_FERR ; 
 int /*<<< orphan*/  E7XXX_DRAM_NERR ; 
 int /*<<< orphan*/  E7XXX_DRAM_UELOG_ADD ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_bits8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void e7xxx_get_error_info(struct mem_ctl_info *mci,
				 struct e7xxx_error_info *info)
{
	struct e7xxx_pvt *pvt;

	pvt = (struct e7xxx_pvt *)mci->pvt_info;
	pci_read_config_byte(pvt->bridge_ck, E7XXX_DRAM_FERR, &info->dram_ferr);
	pci_read_config_byte(pvt->bridge_ck, E7XXX_DRAM_NERR, &info->dram_nerr);

	if ((info->dram_ferr & 1) || (info->dram_nerr & 1)) {
		pci_read_config_dword(pvt->bridge_ck, E7XXX_DRAM_CELOG_ADD,
				&info->dram_celog_add);
		pci_read_config_word(pvt->bridge_ck,
				E7XXX_DRAM_CELOG_SYNDROME,
				&info->dram_celog_syndrome);
	}

	if ((info->dram_ferr & 2) || (info->dram_nerr & 2))
		pci_read_config_dword(pvt->bridge_ck, E7XXX_DRAM_UELOG_ADD,
				&info->dram_uelog_add);

	if (info->dram_ferr & 3)
		pci_write_bits8(pvt->bridge_ck, E7XXX_DRAM_FERR, 0x03, 0x03);

	if (info->dram_nerr & 3)
		pci_write_bits8(pvt->bridge_ck, E7XXX_DRAM_NERR, 0x03, 0x03);
}
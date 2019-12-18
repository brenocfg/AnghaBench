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
typedef  scalar_t__ u32 ;
struct qlcnic_fw_dump {int cap_mask; struct qlcnic_83xx_dump_template_hdr* tmpl_hdr; } ;
struct qlcnic_hardware_context {struct qlcnic_fw_dump fw_dump; } ;
struct qlcnic_adapter {scalar_t__ fw_version; struct pci_dev* pdev; struct qlcnic_hardware_context* ahw; } ;
struct qlcnic_83xx_dump_template_hdr {int drv_cap_mask; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_83xx_extend_md_capab (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_get_fw_version (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_md_check_extended_dump_capability (struct qlcnic_adapter*) ; 
 int qlcnic_fw_cmd_get_minidump_temp (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  vfree (struct qlcnic_83xx_dump_template_hdr*) ; 

void qlcnic_83xx_get_minidump_template(struct qlcnic_adapter *adapter)
{
	u32 prev_version, current_version;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_fw_dump *fw_dump = &ahw->fw_dump;
	struct pci_dev *pdev = adapter->pdev;
	bool extended = false;
	int ret;

	prev_version = adapter->fw_version;
	current_version = qlcnic_83xx_get_fw_version(adapter);

	if (fw_dump->tmpl_hdr == NULL || current_version > prev_version) {
		vfree(fw_dump->tmpl_hdr);

		if (qlcnic_83xx_md_check_extended_dump_capability(adapter))
			extended = !qlcnic_83xx_extend_md_capab(adapter);

		ret = qlcnic_fw_cmd_get_minidump_temp(adapter);
		if (ret)
			return;

		dev_info(&pdev->dev, "Supports FW dump capability\n");

		/* Once we have minidump template with extended iSCSI dump
		 * capability, update the minidump capture mask to 0x1f as
		 * per FW requirement
		 */
		if (extended) {
			struct qlcnic_83xx_dump_template_hdr *hdr;

			hdr = fw_dump->tmpl_hdr;
			hdr->drv_cap_mask = 0x1f;
			fw_dump->cap_mask = 0x1f;
			dev_info(&pdev->dev,
				 "Extended iSCSI dump capability and updated capture mask to 0x1f\n");
		}
	}
}
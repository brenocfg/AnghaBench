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
typedef  int u64 ;
typedef  size_t u32 ;
struct qlcnic_flt_entry {int size; size_t start_addr; } ;
struct qlcnic_adapter {TYPE_1__* ahw; struct pci_dev* pdev; struct firmware* fw; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {size_t fw_type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_BOOTLD_REGION ; 
 int QLCNIC_BOOTLD_START ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_0 ; 
 int QLCNIC_IMAGE_START ; 
 scalar_t__ QLCNIC_ROMUSB_GLB_SW_RESET ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * fw_name ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_get_bootld_offs (struct qlcnic_adapter*) ; 
 int qlcnic_get_flt_entry (struct qlcnic_adapter*,int /*<<< orphan*/ ,struct qlcnic_flt_entry*) ; 
 scalar_t__ qlcnic_get_fw_offs (struct qlcnic_adapter*) ; 
 int qlcnic_get_fw_size (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_pci_mem_write_2M (struct qlcnic_adapter*,size_t,int) ; 
 scalar_t__ qlcnic_rom_fast_read (struct qlcnic_adapter*,size_t,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
qlcnic_load_firmware(struct qlcnic_adapter *adapter)
{
	__le64 *ptr64;
	u32 i, flashaddr, size;
	const struct firmware *fw = adapter->fw;
	struct pci_dev *pdev = adapter->pdev;

	dev_info(&pdev->dev, "loading firmware from %s\n",
		 fw_name[adapter->ahw->fw_type]);

	if (fw) {
		u64 data;

		size = (QLCNIC_IMAGE_START - QLCNIC_BOOTLD_START) / 8;

		ptr64 = (__le64 *)qlcnic_get_bootld_offs(adapter);
		flashaddr = QLCNIC_BOOTLD_START;

		for (i = 0; i < size; i++) {
			data = le64_to_cpu(ptr64[i]);

			if (qlcnic_pci_mem_write_2M(adapter, flashaddr, data))
				return -EIO;

			flashaddr += 8;
		}

		size = qlcnic_get_fw_size(adapter) / 8;

		ptr64 = (__le64 *)qlcnic_get_fw_offs(adapter);
		flashaddr = QLCNIC_IMAGE_START;

		for (i = 0; i < size; i++) {
			data = le64_to_cpu(ptr64[i]);

			if (qlcnic_pci_mem_write_2M(adapter,
						flashaddr, data))
				return -EIO;

			flashaddr += 8;
		}

		size = qlcnic_get_fw_size(adapter) % 8;
		if (size) {
			data = le64_to_cpu(ptr64[i]);

			if (qlcnic_pci_mem_write_2M(adapter,
						flashaddr, data))
				return -EIO;
		}

	} else {
		u64 data;
		u32 hi, lo;
		int ret;
		struct qlcnic_flt_entry bootld_entry;

		ret = qlcnic_get_flt_entry(adapter, QLCNIC_BOOTLD_REGION,
					&bootld_entry);
		if (!ret) {
			size = bootld_entry.size / 8;
			flashaddr = bootld_entry.start_addr;
		} else {
			size = (QLCNIC_IMAGE_START - QLCNIC_BOOTLD_START) / 8;
			flashaddr = QLCNIC_BOOTLD_START;
			dev_info(&pdev->dev,
				"using legacy method to get flash fw region");
		}

		for (i = 0; i < size; i++) {
			if (qlcnic_rom_fast_read(adapter,
					flashaddr, (int *)&lo) != 0)
				return -EIO;
			if (qlcnic_rom_fast_read(adapter,
					flashaddr + 4, (int *)&hi) != 0)
				return -EIO;

			data = (((u64)hi << 32) | lo);

			if (qlcnic_pci_mem_write_2M(adapter,
						flashaddr, data))
				return -EIO;

			flashaddr += 8;
		}
	}
	usleep_range(1000, 1500);

	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x18, 0x1020);
	QLCWR32(adapter, QLCNIC_ROMUSB_GLB_SW_RESET, 0x80001e);
	return 0;
}
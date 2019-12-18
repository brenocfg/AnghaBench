#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct brcmf_pciedev_info {scalar_t__ fw_name; scalar_t__ nvram_name; TYPE_2__* ci; TYPE_1__* pdev; } ;
struct brcmf_bus {int dummy; } ;
struct TYPE_4__ {scalar_t__ rambase; scalar_t__ ramsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMF_PCIE_FW_UP_TIMEOUT ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*,...) ; 
 int /*<<< orphan*/  brcmf_fw_nvram_free (void*) ; 
 int /*<<< orphan*/  brcmf_pcie_copy_mem_todev (struct brcmf_pciedev_info*,scalar_t__,void*,scalar_t__) ; 
 int brcmf_pcie_enter_download_state (struct brcmf_pciedev_info*) ; 
 int brcmf_pcie_exit_download_state (struct brcmf_pciedev_info*,scalar_t__) ; 
 int brcmf_pcie_init_share_ram_info (struct brcmf_pciedev_info*,scalar_t__) ; 
 scalar_t__ brcmf_pcie_read_ram32 (struct brcmf_pciedev_info*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_pcie_write_ram32 (struct brcmf_pciedev_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static int brcmf_pcie_download_fw_nvram(struct brcmf_pciedev_info *devinfo,
					const struct firmware *fw, void *nvram,
					u32 nvram_len)
{
	struct brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	u32 sharedram_addr;
	u32 sharedram_addr_written;
	u32 loop_counter;
	int err;
	u32 address;
	u32 resetintr;

	brcmf_dbg(PCIE, "Halt ARM.\n");
	err = brcmf_pcie_enter_download_state(devinfo);
	if (err)
		return err;

	brcmf_dbg(PCIE, "Download FW %s\n", devinfo->fw_name);
	brcmf_pcie_copy_mem_todev(devinfo, devinfo->ci->rambase,
				  (void *)fw->data, fw->size);

	resetintr = get_unaligned_le32(fw->data);
	release_firmware(fw);

	/* reset last 4 bytes of RAM address. to be used for shared
	 * area. This identifies when FW is running
	 */
	brcmf_pcie_write_ram32(devinfo, devinfo->ci->ramsize - 4, 0);

	if (nvram) {
		brcmf_dbg(PCIE, "Download NVRAM %s\n", devinfo->nvram_name);
		address = devinfo->ci->rambase + devinfo->ci->ramsize -
			  nvram_len;
		brcmf_pcie_copy_mem_todev(devinfo, address, nvram, nvram_len);
		brcmf_fw_nvram_free(nvram);
	} else {
		brcmf_dbg(PCIE, "No matching NVRAM file found %s\n",
			  devinfo->nvram_name);
	}

	sharedram_addr_written = brcmf_pcie_read_ram32(devinfo,
						       devinfo->ci->ramsize -
						       4);
	brcmf_dbg(PCIE, "Bring ARM in running state\n");
	err = brcmf_pcie_exit_download_state(devinfo, resetintr);
	if (err)
		return err;

	brcmf_dbg(PCIE, "Wait for FW init\n");
	sharedram_addr = sharedram_addr_written;
	loop_counter = BRCMF_PCIE_FW_UP_TIMEOUT / 50;
	while ((sharedram_addr == sharedram_addr_written) && (loop_counter)) {
		msleep(50);
		sharedram_addr = brcmf_pcie_read_ram32(devinfo,
						       devinfo->ci->ramsize -
						       4);
		loop_counter--;
	}
	if (sharedram_addr == sharedram_addr_written) {
		brcmf_err(bus, "FW failed to initialize\n");
		return -ENODEV;
	}
	if (sharedram_addr < devinfo->ci->rambase ||
	    sharedram_addr >= devinfo->ci->rambase + devinfo->ci->ramsize) {
		brcmf_err(bus, "Invalid shared RAM address 0x%08x\n",
			  sharedram_addr);
		return -ENODEV;
	}
	brcmf_dbg(PCIE, "Shared RAM addr: 0x%08x\n", sharedram_addr);

	return (brcmf_pcie_init_share_ram_info(devinfo, sharedram_addr));
}
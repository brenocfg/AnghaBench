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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {char* uboot_ver; char* preboot_ver; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__* pcie_bar; TYPE_1__ asic_prop; } ;
typedef  enum goya_fw_component { ____Placeholder_goya_fw_component } goya_fw_component ;

/* Variables and functions */
#define  FW_COMP_PREBOOT 129 
#define  FW_COMP_UBOOT 128 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ SRAM_BASE_ADDR ; 
 size_t SRAM_CFG_BAR_ID ; 
 scalar_t__ SRAM_SIZE ; 
 scalar_t__ VERSION_MAX_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy_fromio (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmPREBOOT_VER_OFFSET ; 
 int /*<<< orphan*/  mmUBOOT_VER_OFFSET ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void goya_read_device_fw_version(struct hl_device *hdev,
					enum goya_fw_component fwc)
{
	const char *name;
	u32 ver_off;
	char *dest;

	switch (fwc) {
	case FW_COMP_UBOOT:
		ver_off = RREG32(mmUBOOT_VER_OFFSET);
		dest = hdev->asic_prop.uboot_ver;
		name = "U-Boot";
		break;
	case FW_COMP_PREBOOT:
		ver_off = RREG32(mmPREBOOT_VER_OFFSET);
		dest = hdev->asic_prop.preboot_ver;
		name = "Preboot";
		break;
	default:
		dev_warn(hdev->dev, "Undefined FW component: %d\n", fwc);
		return;
	}

	ver_off &= ~((u32)SRAM_BASE_ADDR);

	if (ver_off < SRAM_SIZE - VERSION_MAX_LEN) {
		memcpy_fromio(dest, hdev->pcie_bar[SRAM_CFG_BAR_ID] + ver_off,
							VERSION_MAX_LEN);
	} else {
		dev_err(hdev->dev, "%s version offset (0x%x) is above SRAM\n",
								name, ver_off);
		strcpy(dest, "unavailable");
	}
}
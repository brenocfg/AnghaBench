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
struct ptn3460_bridge {char edid_emulation; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  PTN3460_EDID_EMULATION_ADDR ; 
 int PTN3460_EDID_EMULATION_SELECTION ; 
 int PTN3460_EDID_ENABLE_EMULATION ; 
 int /*<<< orphan*/  PTN3460_EDID_SRAM_LOAD_ADDR ; 
 int ptn3460_write_byte (struct ptn3460_bridge*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int ptn3460_select_edid(struct ptn3460_bridge *ptn_bridge)
{
	int ret;
	char val;

	/* Load the selected edid into SRAM (accessed at PTN3460_EDID_ADDR) */
	ret = ptn3460_write_byte(ptn_bridge, PTN3460_EDID_SRAM_LOAD_ADDR,
			ptn_bridge->edid_emulation);
	if (ret) {
		DRM_ERROR("Failed to transfer EDID to sram, ret=%d\n", ret);
		return ret;
	}

	/* Enable EDID emulation and select the desired EDID */
	val = 1 << PTN3460_EDID_ENABLE_EMULATION |
		ptn_bridge->edid_emulation << PTN3460_EDID_EMULATION_SELECTION;

	ret = ptn3460_write_byte(ptn_bridge, PTN3460_EDID_EMULATION_ADDR, val);
	if (ret) {
		DRM_ERROR("Failed to write EDID value, ret=%d\n", ret);
		return ret;
	}

	return 0;
}
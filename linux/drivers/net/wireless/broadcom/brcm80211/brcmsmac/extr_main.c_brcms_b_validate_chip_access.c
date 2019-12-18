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
struct wiphy {int dummy; } ;
struct brcms_hardware {int /*<<< orphan*/  unit; TYPE_1__* wlc; struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;
struct TYPE_2__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ MCTL_GMODE ; 
 scalar_t__ MCTL_IHR_EN ; 
 scalar_t__ MCTL_WAKE ; 
 scalar_t__ OBJADDR_SHM_SEL ; 
 scalar_t__ bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  objaddr ; 
 int /*<<< orphan*/  objdata ; 
 int /*<<< orphan*/  tsf_cfpstart ; 
 int /*<<< orphan*/  wiphy_err (struct wiphy*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 

__attribute__((used)) static bool brcms_b_validate_chip_access(struct brcms_hardware *wlc_hw)
{
	struct bcma_device *core = wlc_hw->d11core;
	u32 w, val;
	struct wiphy *wiphy = wlc_hw->wlc->wiphy;

	/* Validate dchip register access */

	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	w = bcma_read32(core, D11REGOFFS(objdata));

	/* Can we write and read back a 32bit register? */
	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	bcma_write32(core, D11REGOFFS(objdata), (u32) 0xaa5555aa);

	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	val = bcma_read32(core, D11REGOFFS(objdata));
	if (val != (u32) 0xaa5555aa) {
		wiphy_err(wiphy, "wl%d: validate_chip_access: SHM = 0x%x, "
			  "expected 0xaa5555aa\n", wlc_hw->unit, val);
		return false;
	}

	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	bcma_write32(core, D11REGOFFS(objdata), (u32) 0x55aaaa55);

	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	val = bcma_read32(core, D11REGOFFS(objdata));
	if (val != (u32) 0x55aaaa55) {
		wiphy_err(wiphy, "wl%d: validate_chip_access: SHM = 0x%x, "
			  "expected 0x55aaaa55\n", wlc_hw->unit, val);
		return false;
	}

	bcma_write32(core, D11REGOFFS(objaddr), OBJADDR_SHM_SEL | 0);
	(void)bcma_read32(core, D11REGOFFS(objaddr));
	bcma_write32(core, D11REGOFFS(objdata), w);

	/* clear CFPStart */
	bcma_write32(core, D11REGOFFS(tsf_cfpstart), 0);

	w = bcma_read32(core, D11REGOFFS(maccontrol));
	if ((w != (MCTL_IHR_EN | MCTL_WAKE)) &&
	    (w != (MCTL_IHR_EN | MCTL_GMODE | MCTL_WAKE))) {
		wiphy_err(wiphy, "wl%d: validate_chip_access: maccontrol = "
			  "0x%x, expected 0x%x or 0x%x\n", wlc_hw->unit, w,
			  (MCTL_IHR_EN | MCTL_WAKE),
			  (MCTL_IHR_EN | MCTL_GMODE | MCTL_WAKE));
		return false;
	}

	return true;
}
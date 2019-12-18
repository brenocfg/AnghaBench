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
typedef  int u16 ;
struct pci_dev {int revision; int /*<<< orphan*/  bus; } ;
struct intel_cdclk_state {int cdclk; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
#define  GC_CLOCK_100_133 135 
#define  GC_CLOCK_100_200 134 
#define  GC_CLOCK_133_200 133 
#define  GC_CLOCK_133_200_2 132 
#define  GC_CLOCK_133_266 131 
#define  GC_CLOCK_133_266_2 130 
#define  GC_CLOCK_166_250 129 
#define  GC_CLOCK_166_266 128 
 int GC_CLOCK_CONTROL_MASK ; 
 int /*<<< orphan*/  HPLLCC ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_bus_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void i85x_get_cdclk(struct drm_i915_private *dev_priv,
			   struct intel_cdclk_state *cdclk_state)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	u16 hpllcc = 0;

	/*
	 * 852GM/852GMV only supports 133 MHz and the HPLLCC
	 * encoding is different :(
	 * FIXME is this the right way to detect 852GM/852GMV?
	 */
	if (pdev->revision == 0x1) {
		cdclk_state->cdclk = 133333;
		return;
	}

	pci_bus_read_config_word(pdev->bus,
				 PCI_DEVFN(0, 3), HPLLCC, &hpllcc);

	/* Assume that the hardware is in the high speed state.  This
	 * should be the default.
	 */
	switch (hpllcc & GC_CLOCK_CONTROL_MASK) {
	case GC_CLOCK_133_200:
	case GC_CLOCK_133_200_2:
	case GC_CLOCK_100_200:
		cdclk_state->cdclk = 200000;
		break;
	case GC_CLOCK_166_250:
		cdclk_state->cdclk = 250000;
		break;
	case GC_CLOCK_100_133:
		cdclk_state->cdclk = 133333;
		break;
	case GC_CLOCK_133_266:
	case GC_CLOCK_133_266_2:
	case GC_CLOCK_166_266:
		cdclk_state->cdclk = 266667;
		break;
	}
}
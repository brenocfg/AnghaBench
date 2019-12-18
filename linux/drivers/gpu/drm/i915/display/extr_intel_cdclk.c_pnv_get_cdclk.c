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
struct pci_dev {int dummy; } ;
struct intel_cdclk_state {int cdclk; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GCFGC ; 
#define  GC_DISPLAY_CLOCK_133_MHZ_PNV 133 
#define  GC_DISPLAY_CLOCK_167_MHZ_PNV 132 
#define  GC_DISPLAY_CLOCK_200_MHZ_PNV 131 
#define  GC_DISPLAY_CLOCK_267_MHZ_PNV 130 
#define  GC_DISPLAY_CLOCK_333_MHZ_PNV 129 
#define  GC_DISPLAY_CLOCK_444_MHZ_PNV 128 
 int GC_DISPLAY_CLOCK_MASK ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void pnv_get_cdclk(struct drm_i915_private *dev_priv,
			  struct intel_cdclk_state *cdclk_state)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	u16 gcfgc = 0;

	pci_read_config_word(pdev, GCFGC, &gcfgc);

	switch (gcfgc & GC_DISPLAY_CLOCK_MASK) {
	case GC_DISPLAY_CLOCK_267_MHZ_PNV:
		cdclk_state->cdclk = 266667;
		break;
	case GC_DISPLAY_CLOCK_333_MHZ_PNV:
		cdclk_state->cdclk = 333333;
		break;
	case GC_DISPLAY_CLOCK_444_MHZ_PNV:
		cdclk_state->cdclk = 444444;
		break;
	case GC_DISPLAY_CLOCK_200_MHZ_PNV:
		cdclk_state->cdclk = 200000;
		break;
	default:
		DRM_ERROR("Unknown pnv display core clock 0x%04x\n", gcfgc);
		/* fall through */
	case GC_DISPLAY_CLOCK_133_MHZ_PNV:
		cdclk_state->cdclk = 133333;
		break;
	case GC_DISPLAY_CLOCK_167_MHZ_PNV:
		cdclk_state->cdclk = 166667;
		break;
	}
}
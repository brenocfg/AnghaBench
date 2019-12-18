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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct intel_cdclk_state {int vco; int cdclk; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int DIV_ROUND_CLOSEST (int,int const) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  GCFGC ; 
 int intel_hpll_vco (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void i965gm_get_cdclk(struct drm_i915_private *dev_priv,
			     struct intel_cdclk_state *cdclk_state)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	static const u8 div_3200[] = { 16, 10,  8 };
	static const u8 div_4000[] = { 20, 12, 10 };
	static const u8 div_5333[] = { 24, 16, 14 };
	const u8 *div_table;
	unsigned int cdclk_sel;
	u16 tmp = 0;

	cdclk_state->vco = intel_hpll_vco(dev_priv);

	pci_read_config_word(pdev, GCFGC, &tmp);

	cdclk_sel = ((tmp >> 8) & 0x1f) - 1;

	if (cdclk_sel >= ARRAY_SIZE(div_3200))
		goto fail;

	switch (cdclk_state->vco) {
	case 3200000:
		div_table = div_3200;
		break;
	case 4000000:
		div_table = div_4000;
		break;
	case 5333333:
		div_table = div_5333;
		break;
	default:
		goto fail;
	}

	cdclk_state->cdclk = DIV_ROUND_CLOSEST(cdclk_state->vco,
					       div_table[cdclk_sel]);
	return;

fail:
	DRM_ERROR("Unable to determine CDCLK. HPLL VCO=%u kHz, CFGC=0x%04x\n",
		  cdclk_state->vco, tmp);
	cdclk_state->cdclk = 200000;
}
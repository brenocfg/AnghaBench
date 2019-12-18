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

__attribute__((used)) static void g33_get_cdclk(struct drm_i915_private *dev_priv,
			  struct intel_cdclk_state *cdclk_state)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	static const u8 div_3200[] = { 12, 10,  8,  7, 5, 16 };
	static const u8 div_4000[] = { 14, 12, 10,  8, 6, 20 };
	static const u8 div_4800[] = { 20, 14, 12, 10, 8, 24 };
	static const u8 div_5333[] = { 20, 16, 12, 12, 8, 28 };
	const u8 *div_table;
	unsigned int cdclk_sel;
	u16 tmp = 0;

	cdclk_state->vco = intel_hpll_vco(dev_priv);

	pci_read_config_word(pdev, GCFGC, &tmp);

	cdclk_sel = (tmp >> 4) & 0x7;

	if (cdclk_sel >= ARRAY_SIZE(div_3200))
		goto fail;

	switch (cdclk_state->vco) {
	case 3200000:
		div_table = div_3200;
		break;
	case 4000000:
		div_table = div_4000;
		break;
	case 4800000:
		div_table = div_4800;
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
	DRM_ERROR("Unable to determine CDCLK. HPLL VCO=%u kHz, CFGC=0x%08x\n",
		  cdclk_state->vco, tmp);
	cdclk_state->cdclk = 190476;
}
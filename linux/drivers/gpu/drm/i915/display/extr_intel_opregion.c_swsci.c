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
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct opregion_swsci {int dslp; int scic; int parm; } ;
struct TYPE_4__ {int swsci_sbcb_sub_functions; int swsci_gbda_sub_functions; struct opregion_swsci* swsci; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_2__ opregion; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO_ONCE (char*,int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int MAX_DSLP ; 
 int /*<<< orphan*/  SWSCI ; 
 int SWSCI_GBDA ; 
 int SWSCI_GSSCIE ; 
 int SWSCI_SBCB ; 
 int SWSCI_SCIC_EXIT_STATUS_MASK ; 
 int SWSCI_SCIC_EXIT_STATUS_SHIFT ; 
 int SWSCI_SCIC_EXIT_STATUS_SUCCESS ; 
 int SWSCI_SCIC_INDICATOR ; 
 int SWSCI_SCIC_MAIN_FUNCTION_MASK ; 
 int SWSCI_SCIC_MAIN_FUNCTION_SHIFT ; 
 int SWSCI_SCIC_SUB_FUNCTION_MASK ; 
 int SWSCI_SCIC_SUB_FUNCTION_SHIFT ; 
 int SWSCI_SCISEL ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int swsci(struct drm_i915_private *dev_priv,
		 u32 function, u32 parm, u32 *parm_out)
{
	struct opregion_swsci *swsci = dev_priv->opregion.swsci;
	struct pci_dev *pdev = dev_priv->drm.pdev;
	u32 main_function, sub_function, scic;
	u16 swsci_val;
	u32 dslp;

	if (!swsci)
		return -ENODEV;

	main_function = (function & SWSCI_SCIC_MAIN_FUNCTION_MASK) >>
		SWSCI_SCIC_MAIN_FUNCTION_SHIFT;
	sub_function = (function & SWSCI_SCIC_SUB_FUNCTION_MASK) >>
		SWSCI_SCIC_SUB_FUNCTION_SHIFT;

	/* Check if we can call the function. See swsci_setup for details. */
	if (main_function == SWSCI_SBCB) {
		if ((dev_priv->opregion.swsci_sbcb_sub_functions &
		     (1 << sub_function)) == 0)
			return -EINVAL;
	} else if (main_function == SWSCI_GBDA) {
		if ((dev_priv->opregion.swsci_gbda_sub_functions &
		     (1 << sub_function)) == 0)
			return -EINVAL;
	}

	/* Driver sleep timeout in ms. */
	dslp = swsci->dslp;
	if (!dslp) {
		/* The spec says 2ms should be the default, but it's too small
		 * for some machines. */
		dslp = 50;
	} else if (dslp > MAX_DSLP) {
		/* Hey bios, trust must be earned. */
		DRM_INFO_ONCE("ACPI BIOS requests an excessive sleep of %u ms, "
			      "using %u ms instead\n", dslp, MAX_DSLP);
		dslp = MAX_DSLP;
	}

	/* The spec tells us to do this, but we are the only user... */
	scic = swsci->scic;
	if (scic & SWSCI_SCIC_INDICATOR) {
		DRM_DEBUG_DRIVER("SWSCI request already in progress\n");
		return -EBUSY;
	}

	scic = function | SWSCI_SCIC_INDICATOR;

	swsci->parm = parm;
	swsci->scic = scic;

	/* Ensure SCI event is selected and event trigger is cleared. */
	pci_read_config_word(pdev, SWSCI, &swsci_val);
	if (!(swsci_val & SWSCI_SCISEL) || (swsci_val & SWSCI_GSSCIE)) {
		swsci_val |= SWSCI_SCISEL;
		swsci_val &= ~SWSCI_GSSCIE;
		pci_write_config_word(pdev, SWSCI, swsci_val);
	}

	/* Use event trigger to tell bios to check the mail. */
	swsci_val |= SWSCI_GSSCIE;
	pci_write_config_word(pdev, SWSCI, swsci_val);

	/* Poll for the result. */
#define C (((scic = swsci->scic) & SWSCI_SCIC_INDICATOR) == 0)
	if (wait_for(C, dslp)) {
		DRM_DEBUG_DRIVER("SWSCI request timed out\n");
		return -ETIMEDOUT;
	}

	scic = (scic & SWSCI_SCIC_EXIT_STATUS_MASK) >>
		SWSCI_SCIC_EXIT_STATUS_SHIFT;

	/* Note: scic == 0 is an error! */
	if (scic != SWSCI_SCIC_EXIT_STATUS_SUCCESS) {
		DRM_DEBUG_DRIVER("SWSCI request error %u\n", scic);
		return -EIO;
	}

	if (parm_out)
		*parm_out = swsci->parm;

	return 0;

#undef C
}
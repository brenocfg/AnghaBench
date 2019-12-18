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
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct igc_hw {TYPE_1__ mac; } ;
struct igc_adapter {int num_q_vectors; int /*<<< orphan*/ * q_vector; int /*<<< orphan*/  eims_other; int /*<<< orphan*/  eims_enable_mask; struct igc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IGC_GPIE ; 
 int IGC_GPIE_EIAME ; 
 int IGC_GPIE_MSIX_MODE ; 
 int IGC_GPIE_NSICR ; 
 int IGC_GPIE_PBA ; 
 int /*<<< orphan*/  IGC_IVAR_MISC ; 
 int IGC_IVAR_VALID ; 
 int /*<<< orphan*/  igc_assign_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  igc_i225 128 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igc_configure_msix(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;
	int i, vector = 0;
	u32 tmp;

	adapter->eims_enable_mask = 0;

	/* set vector for other causes, i.e. link changes */
	switch (hw->mac.type) {
	case igc_i225:
		/* Turn on MSI-X capability first, or our settings
		 * won't stick.  And it will take days to debug.
		 */
		wr32(IGC_GPIE, IGC_GPIE_MSIX_MODE |
		     IGC_GPIE_PBA | IGC_GPIE_EIAME |
		     IGC_GPIE_NSICR);

		/* enable msix_other interrupt */
		adapter->eims_other = BIT(vector);
		tmp = (vector++ | IGC_IVAR_VALID) << 8;

		wr32(IGC_IVAR_MISC, tmp);
		break;
	default:
		/* do nothing, since nothing else supports MSI-X */
		break;
	} /* switch (hw->mac.type) */

	adapter->eims_enable_mask |= adapter->eims_other;

	for (i = 0; i < adapter->num_q_vectors; i++)
		igc_assign_vector(adapter->q_vector[i], vector++);

	wrfl();
}
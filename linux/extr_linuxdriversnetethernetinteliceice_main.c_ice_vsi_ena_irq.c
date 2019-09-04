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
struct ice_vsi {int num_q_vectors; int /*<<< orphan*/ * q_vectors; struct ice_pf* back; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {int /*<<< orphan*/  flags; struct ice_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_irq_dynamic_ena (struct ice_hw*,struct ice_vsi*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_ena_irq(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;

	if (test_bit(ICE_FLAG_MSIX_ENA, pf->flags)) {
		int i;

		for (i = 0; i < vsi->num_q_vectors; i++)
			ice_irq_dynamic_ena(hw, vsi, vsi->q_vectors[i]);
	}

	ice_flush(hw);
	return 0;
}
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
struct ice_vsi {struct ice_pf* back; } ;
struct ice_pf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 int ice_vsi_req_irq_msix (struct ice_vsi*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_req_irq(struct ice_vsi *vsi, char *basename)
{
	struct ice_pf *pf = vsi->back;
	int err = -EINVAL;

	if (test_bit(ICE_FLAG_MSIX_ENA, pf->flags))
		err = ice_vsi_req_irq_msix(vsi, basename);

	return err;
}
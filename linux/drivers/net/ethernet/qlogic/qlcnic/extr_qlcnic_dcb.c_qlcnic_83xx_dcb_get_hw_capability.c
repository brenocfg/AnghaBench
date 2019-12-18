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
struct qlcnic_dcb_capability {int dcb_capability; scalar_t__ ets_capability; scalar_t__ tsa_capability; } ;
struct qlcnic_dcb {int /*<<< orphan*/  state; TYPE_1__* cfg; } ;
struct TYPE_2__ {struct qlcnic_dcb_capability capability; } ;

/* Variables and functions */
 int BIT_2 ; 
 int BIT_3 ; 
 int DCB_CAP_DCBX_LLD_MANAGED ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 int DCB_CAP_DCBX_VER_IEEE ; 
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int __qlcnic_dcb_get_capability (struct qlcnic_dcb*,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_83xx_dcb_get_hw_capability(struct qlcnic_dcb *dcb)
{
	struct qlcnic_dcb_capability *cap = &dcb->cfg->capability;
	u32 mbx_out;
	int err;

	err = __qlcnic_dcb_get_capability(dcb, &mbx_out);
	if (err)
		return err;

	if (mbx_out & BIT_2)
		cap->dcb_capability = DCB_CAP_DCBX_VER_CEE;
	if (mbx_out & BIT_3)
		cap->dcb_capability |= DCB_CAP_DCBX_VER_IEEE;
	if (cap->dcb_capability)
		cap->dcb_capability |= DCB_CAP_DCBX_LLD_MANAGED;

	if (cap->dcb_capability && cap->tsa_capability && cap->ets_capability)
		set_bit(QLCNIC_DCB_STATE, &dcb->state);

	return err;
}
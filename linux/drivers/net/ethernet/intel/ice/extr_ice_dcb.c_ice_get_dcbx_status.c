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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRTDCB_GENS ; 
 int PRTDCB_GENS_DCBX_STATUS_M ; 
 int PRTDCB_GENS_DCBX_STATUS_S ; 
 int rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ice_get_dcbx_status(struct ice_hw *hw)
{
	u32 reg;

	reg = rd32(hw, PRTDCB_GENS);
	return (u8)((reg & PRTDCB_GENS_DCBX_STATUS_M) >>
		    PRTDCB_GENS_DCBX_STATUS_S);
}
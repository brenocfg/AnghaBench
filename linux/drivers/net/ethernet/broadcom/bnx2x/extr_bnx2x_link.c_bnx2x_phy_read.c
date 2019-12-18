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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct link_params {size_t num_phys; TYPE_1__* phy; int /*<<< orphan*/  bp; } ;
struct TYPE_2__ {size_t addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int bnx2x_cl45_read (int /*<<< orphan*/ ,TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_phy_read(struct link_params *params, u8 phy_addr,
		   u8 devad, u16 reg, u16 *ret_val)
{
	u8 phy_index;
	/* Probe for the phy according to the given phy_addr, and execute
	 * the read request on it
	 */
	for (phy_index = 0; phy_index < params->num_phys; phy_index++) {
		if (params->phy[phy_index].addr == phy_addr) {
			return bnx2x_cl45_read(params->bp,
					       &params->phy[phy_index], devad,
					       reg, ret_val);
		}
	}
	return -EINVAL;
}
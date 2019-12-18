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
struct TYPE_3__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int EBUSY ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int IXGBE_MSCA_ADDR_CYCLE ; 
 int IXGBE_MSCA_DEV_TYPE_SHIFT ; 
 int IXGBE_MSCA_MDI_COMMAND ; 
 int IXGBE_MSCA_OLD_PROTOCOL ; 
 int IXGBE_MSCA_PHY_ADDR_SHIFT ; 
 int IXGBE_MSCA_READ ; 
 int IXGBE_MSCA_READ_AUTOINC ; 
 int /*<<< orphan*/  IXGBE_MSRWD ; 
 int IXGBE_MSRWD_READ_DATA_SHIFT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int MII_ADDR_C45 ; 
 int ixgbe_msca_cmd (struct ixgbe_hw*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int) ; 

__attribute__((used)) static s32 ixgbe_mii_bus_read_generic(struct ixgbe_hw *hw, int addr,
				      int regnum, u32 gssr)
{
	u32 hwaddr, cmd;
	s32 data;

	if (hw->mac.ops.acquire_swfw_sync(hw, gssr))
		return -EBUSY;

	hwaddr = addr << IXGBE_MSCA_PHY_ADDR_SHIFT;
	if (regnum & MII_ADDR_C45) {
		hwaddr |= regnum & GENMASK(21, 0);
		cmd = hwaddr | IXGBE_MSCA_ADDR_CYCLE | IXGBE_MSCA_MDI_COMMAND;
	} else {
		hwaddr |= (regnum & GENMASK(5, 0)) << IXGBE_MSCA_DEV_TYPE_SHIFT;
		cmd = hwaddr | IXGBE_MSCA_OLD_PROTOCOL |
			IXGBE_MSCA_READ_AUTOINC | IXGBE_MSCA_MDI_COMMAND;
	}

	data = ixgbe_msca_cmd(hw, cmd);
	if (data < 0)
		goto mii_bus_read_done;

	/* For a clause 45 access the address cycle just completed, we still
	 * need to do the read command, otherwise just get the data
	 */
	if (!(regnum & MII_ADDR_C45))
		goto do_mii_bus_read;

	cmd = hwaddr | IXGBE_MSCA_READ | IXGBE_MSCA_MDI_COMMAND;
	data = ixgbe_msca_cmd(hw, cmd);
	if (data < 0)
		goto mii_bus_read_done;

do_mii_bus_read:
	data = IXGBE_READ_REG(hw, IXGBE_MSRWD);
	data = (data >> IXGBE_MSRWD_READ_DATA_SHIFT) & GENMASK(16, 0);

mii_bus_read_done:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	return data;
}
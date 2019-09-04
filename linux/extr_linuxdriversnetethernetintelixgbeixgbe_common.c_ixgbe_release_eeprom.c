#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int semaphore_delay; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_3__ ops; } ;
struct ixgbe_hw {TYPE_1__ eeprom; TYPE_2__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EEC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_EEC_CS ; 
 int /*<<< orphan*/  IXGBE_EEC_REQ ; 
 int /*<<< orphan*/  IXGBE_EEC_SK ; 
 int /*<<< orphan*/  IXGBE_GSSR_EEP_SM ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ixgbe_release_eeprom(struct ixgbe_hw *hw)
{
	u32 eec;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	eec |= IXGBE_EEC_CS;  /* Pull CS high */
	eec &= ~IXGBE_EEC_SK; /* Lower SCK */

	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);

	udelay(1);

	/* Stop requesting EEPROM access */
	eec &= ~IXGBE_EEC_REQ;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);

	/*
	 * Delay before attempt to obtain semaphore again to allow FW
	 * access. semaphore_delay is in ms we need us for usleep_range
	 */
	usleep_range(hw->eeprom.semaphore_delay * 1000,
		     hw->eeprom.semaphore_delay * 2000);
}
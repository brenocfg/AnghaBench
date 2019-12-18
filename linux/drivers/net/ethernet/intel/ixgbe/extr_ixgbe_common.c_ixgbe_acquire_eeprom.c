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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EEC (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_EEC_CS ; 
 scalar_t__ IXGBE_EEC_GNT ; 
 scalar_t__ IXGBE_EEC_REQ ; 
 scalar_t__ IXGBE_EEC_SK ; 
 scalar_t__ IXGBE_EEPROM_GRANT_ATTEMPTS ; 
 int /*<<< orphan*/  IXGBE_ERR_EEPROM ; 
 int /*<<< orphan*/  IXGBE_ERR_SWFW_SYNC ; 
 int /*<<< orphan*/  IXGBE_GSSR_EEP_SM ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_acquire_eeprom(struct ixgbe_hw *hw)
{
	u32 eec;
	u32 i;

	if (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM) != 0)
		return IXGBE_ERR_SWFW_SYNC;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	/* Request EEPROM Access */
	eec |= IXGBE_EEC_REQ;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);

	for (i = 0; i < IXGBE_EEPROM_GRANT_ATTEMPTS; i++) {
		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		if (eec & IXGBE_EEC_GNT)
			break;
		udelay(5);
	}

	/* Release if grant not acquired */
	if (!(eec & IXGBE_EEC_GNT)) {
		eec &= ~IXGBE_EEC_REQ;
		IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
		hw_dbg(hw, "Could not acquire EEPROM grant\n");

		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
		return IXGBE_ERR_EEPROM;
	}

	/* Setup EEPROM for Read/Write */
	/* Clear CS and SK */
	eec &= ~(IXGBE_EEC_CS | IXGBE_EEC_SK);
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
	return 0;
}
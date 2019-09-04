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
typedef  int u16 ;
struct ksz_hw {int /*<<< orphan*/  features; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPEED_125_MHZ ; 
 int /*<<< orphan*/  HALF_DUPLEX_SIGNAL_BUG ; 
 scalar_t__ KS884X_BUS_CTRL_OFFSET ; 
 int KS884X_CHIP_ID_MASK_41 ; 
 scalar_t__ KS884X_CHIP_ID_OFFSET ; 
 int KS884X_REVISION_MASK ; 
 int KS884X_REVISION_SHIFT ; 
 int REG_CHIP_ID_41 ; 
 int REG_CHIP_ID_42 ; 
 int /*<<< orphan*/  SMALL_PACKET_TX_BUG ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hw_init(struct ksz_hw *hw)
{
	int rc = 0;
	u16 data;
	u16 revision;

	/* Set bus speed to 125MHz. */
	writew(BUS_SPEED_125_MHZ, hw->io + KS884X_BUS_CTRL_OFFSET);

	/* Check KSZ884x chip ID. */
	data = readw(hw->io + KS884X_CHIP_ID_OFFSET);

	revision = (data & KS884X_REVISION_MASK) >> KS884X_REVISION_SHIFT;
	data &= KS884X_CHIP_ID_MASK_41;
	if (REG_CHIP_ID_41 == data)
		rc = 1;
	else if (REG_CHIP_ID_42 == data)
		rc = 2;
	else
		return 0;

	/* Setup hardware features or bug workarounds. */
	if (revision <= 1) {
		hw->features |= SMALL_PACKET_TX_BUG;
		if (1 == rc)
			hw->features |= HALF_DUPLEX_SIGNAL_BUG;
	}
	return rc;
}
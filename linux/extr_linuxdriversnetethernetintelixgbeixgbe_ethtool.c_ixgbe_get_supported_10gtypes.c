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
struct TYPE_2__ {int /*<<< orphan*/  media_type; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;

/* Variables and functions */
#define  IXGBE_DEV_ID_82598 135 
#define  IXGBE_DEV_ID_82598_BX 134 
#define  IXGBE_DEV_ID_82599_KR 133 
#define  IXGBE_DEV_ID_82599_KX4 132 
#define  IXGBE_DEV_ID_82599_KX4_MEZZ 131 
#define  IXGBE_DEV_ID_X550EM_X_KR 130 
#define  IXGBE_DEV_ID_X550EM_X_KX4 129 
#define  IXGBE_DEV_ID_X550EM_X_XFI 128 
 int SUPPORTED_10000baseKR_Full ; 
 int SUPPORTED_10000baseKX4_Full ; 
 int SUPPORTED_10000baseT_Full ; 
 int /*<<< orphan*/  ixgbe_isbackplane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ixgbe_get_supported_10gtypes(struct ixgbe_hw *hw)
{
	if (!ixgbe_isbackplane(hw->phy.media_type))
		return SUPPORTED_10000baseT_Full;

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82598:
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_X550EM_X_KX4:
		return SUPPORTED_10000baseKX4_Full;
	case IXGBE_DEV_ID_82598_BX:
	case IXGBE_DEV_ID_82599_KR:
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_X_XFI:
		return SUPPORTED_10000baseKR_Full;
	default:
		return SUPPORTED_10000baseKX4_Full |
		       SUPPORTED_10000baseKR_Full;
	}
}
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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_MII 130 
#define  PHY_INTERFACE_MODE_RMII 129 
#define  PHY_INTERFACE_MODE_SMII 128 
 int /*<<< orphan*/  ZMII_FER_MII (int) ; 
 int /*<<< orphan*/  ZMII_FER_RMII (int) ; 
 int /*<<< orphan*/  ZMII_FER_SMII (int) ; 

__attribute__((used)) static inline u32 zmii_mode_mask(int mode, int input)
{
	switch (mode) {
	case PHY_INTERFACE_MODE_MII:
		return ZMII_FER_MII(input);
	case PHY_INTERFACE_MODE_RMII:
		return ZMII_FER_RMII(input);
	case PHY_INTERFACE_MODE_SMII:
		return ZMII_FER_SMII(input);
	default:
		return 0;
	}
}
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
struct madera_pin_private {int dummy; } ;

/* Variables and functions */
 int MADERA_GP1_DRV_STR_MASK ; 
 int MADERA_GP1_DRV_STR_SHIFT ; 

__attribute__((used)) static unsigned int madera_pin_unmake_drv_str(struct madera_pin_private *priv,
					      u16 regval)
{
	regval = (regval & MADERA_GP1_DRV_STR_MASK) >> MADERA_GP1_DRV_STR_SHIFT;

	switch (regval) {
	case 0:
		return 4;
	case 2:
		return 8;
	default:
		return 0;
	}
}
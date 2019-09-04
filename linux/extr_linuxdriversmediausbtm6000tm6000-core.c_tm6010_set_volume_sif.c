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
typedef  int u8 ;
struct tm6000_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TM6010_REQ08_R07_A_LEFT_VOL ; 
 int /*<<< orphan*/  TM6010_REQ08_R08_A_RIGHT_VOL ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tm6010_set_volume_sif(struct tm6000_core *dev, int vol)
{
	u8 vol_reg;

	vol_reg = vol & 0x0F;

	if (vol < 0)
		vol_reg |= 0x40;

	tm6000_set_reg(dev, TM6010_REQ08_R07_A_LEFT_VOL, vol_reg);
	tm6000_set_reg(dev, TM6010_REQ08_R08_A_RIGHT_VOL, vol_reg);
}
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
struct xiic_i2c {int dummy; } ;

/* Variables and functions */
 int XIIC_CR_ENABLE_DEVICE_MASK ; 
 int /*<<< orphan*/  XIIC_CR_REG_OFFSET ; 
 int /*<<< orphan*/  XIIC_RESETR_OFFSET ; 
 int /*<<< orphan*/  XIIC_RESET_MASK ; 
 int xiic_getreg8 (struct xiic_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xiic_setreg32 (struct xiic_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xiic_setreg8 (struct xiic_i2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xiic_deinit(struct xiic_i2c *i2c)
{
	u8 cr;

	xiic_setreg32(i2c, XIIC_RESETR_OFFSET, XIIC_RESET_MASK);

	/* Disable IIC Device. */
	cr = xiic_getreg8(i2c, XIIC_CR_REG_OFFSET);
	xiic_setreg8(i2c, XIIC_CR_REG_OFFSET, cr & ~XIIC_CR_ENABLE_DEVICE_MASK);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct stimx274 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX274_DIGITAL_GAIN_REG ; 
 int IMX274_MASK_LSB_4_BITS ; 
 int clamp (int,int,int) ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int imx274_write_reg (struct stimx274*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imx274_set_digital_gain(struct stimx274 *priv, u32 dgain)
{
	u8 reg_val;

	reg_val = ffs(dgain);

	if (reg_val)
		reg_val--;

	reg_val = clamp(reg_val, (u8)0, (u8)3);

	return imx274_write_reg(priv, IMX274_DIGITAL_GAIN_REG,
				reg_val & IMX274_MASK_LSB_4_BITS);
}
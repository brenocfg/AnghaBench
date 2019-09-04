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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIN_CFG_EPIO0 ; 
 scalar_t__ PIN_CFG_GPIO0_P0 ; 
 scalar_t__ PIN_CFG_NA ; 
 int /*<<< orphan*/  bnx2x_set_epio (struct bnx2x*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_set_gpio (struct bnx2x*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void bnx2x_set_cfg_pin(struct bnx2x *bp, u32 pin_cfg, u32 val)
{
	if (pin_cfg == PIN_CFG_NA)
		return;
	if (pin_cfg >= PIN_CFG_EPIO0) {
		bnx2x_set_epio(bp, pin_cfg - PIN_CFG_EPIO0, val);
	} else {
		u8 gpio_num = (pin_cfg - PIN_CFG_GPIO0_P0) & 0x3;
		u8 gpio_port = (pin_cfg - PIN_CFG_GPIO0_P0) >> 2;
		bnx2x_set_gpio(bp, gpio_num, (u8)val, gpio_port);
	}
}
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
typedef  int u32 ;
struct intel_gpio {int /*<<< orphan*/  reg; struct drm_psb_private* dev_priv; } ;
struct drm_psb_private {int dummy; } ;

/* Variables and functions */
 int GMBUS_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMBUS_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int GPIO_CLOCK_DIR_MASK ; 
 int GPIO_CLOCK_VAL_IN ; 
 int get_reserved (struct intel_gpio*) ; 

__attribute__((used)) static int get_clock(void *data)
{
	struct intel_gpio *gpio = data;
	struct drm_psb_private *dev_priv = gpio->dev_priv;
	u32 reserved = get_reserved(gpio);
	GMBUS_REG_WRITE(gpio->reg, reserved | GPIO_CLOCK_DIR_MASK);
	GMBUS_REG_WRITE(gpio->reg, reserved);
	return (GMBUS_REG_READ(gpio->reg) & GPIO_CLOCK_VAL_IN) != 0;
}
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
 int GPIO_CLOCK_PULLUP_DISABLE ; 
 int GPIO_DATA_PULLUP_DISABLE ; 

__attribute__((used)) static u32 get_reserved(struct intel_gpio *gpio)
{
	struct drm_psb_private *dev_priv = gpio->dev_priv;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	reserved = GMBUS_REG_READ(gpio->reg) &
				     (GPIO_DATA_PULLUP_DISABLE |
				      GPIO_CLOCK_PULLUP_DISABLE);

	return reserved;
}
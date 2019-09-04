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
struct sunfire_led {int /*<<< orphan*/  reg; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
#define  FHC_CONTROL_LLED 128 
 struct sunfire_led* to_sunfire_led (struct led_classdev*) ; 
 int upa_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upa_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fhc_set(struct led_classdev *led_cdev,
			     enum led_brightness led_val, u32 bit)
{
	struct sunfire_led *p = to_sunfire_led(led_cdev);
	u32 reg = upa_readl(p->reg);

	switch (bit) {
	case FHC_CONTROL_LLED:
		if (led_val)
			reg &= ~bit;
		else
			reg |= bit;
		break;

	default:
		if (led_val)
			reg |= bit;
		else
			reg &= ~bit;
		break;
	}
	upa_writel(reg, p->reg);
}
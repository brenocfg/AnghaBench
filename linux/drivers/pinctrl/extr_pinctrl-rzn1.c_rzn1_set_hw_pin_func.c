#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct rzn1_pinctrl {TYPE_2__* lev2; TYPE_1__* lev1; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * conf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * conf; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int RZN1_FUNC_ETH_MDIO ; 
 int RZN1_FUNC_ETH_MDIO_E1 ; 
 int RZN1_FUNC_L2_OFFSET ; 
 int RZN1_FUNC_MDIO0_E1_HIGHZ ; 
 int RZN1_FUNC_MDIO0_E1_SWITCH ; 
 int RZN1_FUNC_MDIO0_HIGHZ ; 
 int RZN1_FUNC_MDIO0_SWITCH ; 
 int RZN1_FUNC_MDIO1_E1_HIGHZ ; 
 int RZN1_FUNC_MDIO1_E1_SWITCH ; 
 int RZN1_FUNC_MDIO1_HIGHZ ; 
 int RZN1_FUNC_MDIO1_SWITCH ; 
 int RZN1_L1_FUNCTION ; 
 int RZN1_L1_FUNCTION_L2 ; 
 int RZN1_L1_FUNC_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rzn1_pinctrl_mdio_select (struct rzn1_pinctrl*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rzn1_set_hw_pin_func(struct rzn1_pinctrl *ipctl, unsigned int pin,
				u32 pin_config, u8 use_locks)
{
	u32 l1_cache;
	u32 l2_cache;
	u32 l1;
	u32 l2;

	/* Level 3 MDIO multiplexing */
	if (pin_config >= RZN1_FUNC_MDIO0_HIGHZ &&
	    pin_config <= RZN1_FUNC_MDIO1_E1_SWITCH) {
		int mdio_channel;
		u32 mdio_func;

		if (pin_config <= RZN1_FUNC_MDIO1_HIGHZ)
			mdio_channel = 0;
		else
			mdio_channel = 1;

		/* Get MDIO func, and convert the func to the level 2 number */
		if (pin_config <= RZN1_FUNC_MDIO0_SWITCH) {
			mdio_func = pin_config - RZN1_FUNC_MDIO0_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO;
		} else if (pin_config <= RZN1_FUNC_MDIO0_E1_SWITCH) {
			mdio_func = pin_config - RZN1_FUNC_MDIO0_E1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO_E1;
		} else if (pin_config <= RZN1_FUNC_MDIO1_SWITCH) {
			mdio_func = pin_config - RZN1_FUNC_MDIO1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO;
		} else {
			mdio_func = pin_config - RZN1_FUNC_MDIO1_E1_HIGHZ;
			pin_config = RZN1_FUNC_ETH_MDIO_E1;
		}
		rzn1_pinctrl_mdio_select(ipctl, mdio_channel, mdio_func);
	}

	/* Note here, we do not allow anything past the MDIO Mux values */
	if (pin >= ARRAY_SIZE(ipctl->lev1->conf) ||
	    pin_config >= RZN1_FUNC_MDIO0_HIGHZ)
		return -EINVAL;

	l1 = readl(&ipctl->lev1->conf[pin]);
	l1_cache = l1;
	l2 = readl(&ipctl->lev2->conf[pin]);
	l2_cache = l2;

	dev_dbg(ipctl->dev, "setting func for pin %u to %u\n", pin, pin_config);

	l1 &= ~(RZN1_L1_FUNC_MASK << RZN1_L1_FUNCTION);

	if (pin_config < RZN1_FUNC_L2_OFFSET) {
		l1 |= (pin_config << RZN1_L1_FUNCTION);
	} else {
		l1 |= (RZN1_L1_FUNCTION_L2 << RZN1_L1_FUNCTION);

		l2 = pin_config - RZN1_FUNC_L2_OFFSET;
	}

	/* If either configuration changes, we update both anyway */
	if (l1 != l1_cache || l2 != l2_cache) {
		writel(l1, &ipctl->lev1->conf[pin]);
		writel(l2, &ipctl->lev2->conf[pin]);
	}

	return 0;
}
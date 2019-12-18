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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_XIF_CONFIG ; 
 int /*<<< orphan*/  BMAC_XIF_CONFIG_LINK_LED ; 
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  XMAC_CONFIG_FORCE_LED_ON ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_force_led(struct niu *np, int on)
{
	u64 val, reg, bit;

	if (np->flags & NIU_FLAGS_XMAC) {
		reg = XMAC_CONFIG;
		bit = XMAC_CONFIG_FORCE_LED_ON;
	} else {
		reg = BMAC_XIF_CONFIG;
		bit = BMAC_XIF_CONFIG_LINK_LED;
	}

	val = nr64_mac(reg);
	if (on)
		val |= bit;
	else
		val &= ~bit;
	nw64_mac(reg, val);
}
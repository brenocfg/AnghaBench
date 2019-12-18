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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int MII_PHYSID2 ; 
 int /*<<< orphan*/  r8168dp_2_mdio_start (struct rtl8169_private*) ; 
 int /*<<< orphan*/  r8168dp_2_mdio_stop (struct rtl8169_private*) ; 
 int r8169_mdio_read (struct rtl8169_private*,int) ; 

__attribute__((used)) static int r8168dp_2_mdio_read(struct rtl8169_private *tp, int reg)
{
	int value;

	/* Work around issue with chip reporting wrong PHY ID */
	if (reg == MII_PHYSID2)
		return 0xc912;

	r8168dp_2_mdio_start(tp);

	value = r8169_mdio_read(tp, reg);

	r8168dp_2_mdio_stop(tp);

	return value;
}
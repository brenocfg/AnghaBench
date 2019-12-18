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
 int /*<<< orphan*/  r8168dp_2_mdio_start (struct rtl8169_private*) ; 
 int /*<<< orphan*/  r8168dp_2_mdio_stop (struct rtl8169_private*) ; 
 int /*<<< orphan*/  r8169_mdio_write (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void r8168dp_2_mdio_write(struct rtl8169_private *tp, int reg, int value)
{
	r8168dp_2_mdio_start(tp);

	r8169_mdio_write(tp, reg, value);

	r8168dp_2_mdio_stop(tp);
}
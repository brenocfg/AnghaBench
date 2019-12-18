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
 int /*<<< orphan*/  EPHY_RXER_NUM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OCPAR ; 
 int /*<<< orphan*/  OCPAR_GPHY_READ_CMD ; 
 int /*<<< orphan*/  OCPDR ; 
 int OCPDR_DATA_MASK ; 
 int /*<<< orphan*/  OCPDR_READ_CMD ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  r8168dp_1_mdio_access (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_ocpar_cond ; 
 scalar_t__ rtl_udelay_loop_wait_high (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int r8168dp_1_mdio_read(struct rtl8169_private *tp, int reg)
{
	r8168dp_1_mdio_access(tp, reg, OCPDR_READ_CMD);

	mdelay(1);
	RTL_W32(tp, OCPAR, OCPAR_GPHY_READ_CMD);
	RTL_W32(tp, EPHY_RXER_NUM, 0);

	return rtl_udelay_loop_wait_high(tp, &rtl_ocpar_cond, 1000, 100) ?
		RTL_R32(tp, OCPDR) & OCPDR_DATA_MASK : -ETIMEDOUT;
}
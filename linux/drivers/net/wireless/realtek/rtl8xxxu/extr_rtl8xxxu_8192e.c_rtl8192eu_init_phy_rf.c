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
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_A ; 
 int /*<<< orphan*/  RF_B ; 
 int /*<<< orphan*/  rtl8192eu_radioa_init_table ; 
 int /*<<< orphan*/  rtl8192eu_radiob_init_table ; 
 int rtl8xxxu_init_phy_rf (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8192eu_init_phy_rf(struct rtl8xxxu_priv *priv)
{
	int ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8192eu_radioa_init_table, RF_A);
	if (ret)
		goto exit;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8192eu_radiob_init_table, RF_B);

exit:
	return ret;
}
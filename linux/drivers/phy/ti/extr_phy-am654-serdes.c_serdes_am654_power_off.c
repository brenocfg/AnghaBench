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
struct serdes_am654 {int dummy; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct serdes_am654* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  serdes_am654_disable_pll (struct serdes_am654*) ; 
 int /*<<< orphan*/  serdes_am654_disable_txrx (struct serdes_am654*) ; 

__attribute__((used)) static int serdes_am654_power_off(struct phy *x)
{
	struct serdes_am654 *phy = phy_get_drvdata(x);

	serdes_am654_disable_txrx(phy);
	serdes_am654_disable_pll(phy);

	return 0;
}
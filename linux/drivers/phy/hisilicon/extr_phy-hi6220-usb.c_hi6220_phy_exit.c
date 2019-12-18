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
struct phy {int dummy; } ;
struct hi6220_priv {int dummy; } ;

/* Variables and functions */
 int hi6220_phy_setup (struct hi6220_priv*,int) ; 
 struct hi6220_priv* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int hi6220_phy_exit(struct phy *phy)
{
	struct hi6220_priv *priv = phy_get_drvdata(phy);

	return hi6220_phy_setup(priv, false);
}
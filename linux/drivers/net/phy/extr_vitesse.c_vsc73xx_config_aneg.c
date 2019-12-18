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
struct phy_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int vsc73xx_config_aneg(struct phy_device *phydev)
{
	/* The VSC73xx switches does not like to be instructed to
	 * do autonegotiation in any way, it prefers that you just go
	 * with the power-on/reset defaults. Writing some registers will
	 * just make autonegotiation permanently fail.
	 */
	return 0;
}
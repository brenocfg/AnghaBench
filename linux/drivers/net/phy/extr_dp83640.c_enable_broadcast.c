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
 int BC_WRITE ; 
 int /*<<< orphan*/  PAGESEL ; 
 int /*<<< orphan*/  PHYCR2 ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_broadcast(struct phy_device *phydev, int init_page, int on)
{
	int val;
	phy_write(phydev, PAGESEL, 0);
	val = phy_read(phydev, PHYCR2);
	if (on)
		val |= BC_WRITE;
	else
		val &= ~BC_WRITE;
	phy_write(phydev, PHYCR2, val);
	phy_write(phydev, PAGESEL, init_page);
}
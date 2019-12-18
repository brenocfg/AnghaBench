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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_EXP_MEM_ADD ; 
 int /*<<< orphan*/  NS_EXP_MEM_DATA ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ns_exp_write(struct phy_device *phydev, u16 reg, u8 data)
{
	phy_write(phydev, NS_EXP_MEM_ADD, reg);
	phy_write(phydev, NS_EXP_MEM_DATA, data);
}
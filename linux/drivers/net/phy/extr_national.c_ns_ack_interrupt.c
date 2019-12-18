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
 int /*<<< orphan*/  DP83865_INT_CLEAR ; 
 int /*<<< orphan*/  DP83865_INT_STATUS ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ns_ack_interrupt(struct phy_device *phydev)
{
	int ret = phy_read(phydev, DP83865_INT_STATUS);
	if (ret < 0)
		return ret;

	/* Clear the interrupt status bit by writing a “1”
	 * to the corresponding bit in INT_CLEAR (2:0 are reserved) */
	ret = phy_write(phydev, DP83865_INT_CLEAR, ret & ~0x7);

	return ret;
}
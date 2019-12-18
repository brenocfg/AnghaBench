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
typedef  int /*<<< orphan*/  u32 ;
struct isp1704_charger {int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int usb_phy_io_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int isp1704_write(struct isp1704_charger *isp, u32 reg, u32 val)
{
	return usb_phy_io_write(isp->phy, val, reg);
}
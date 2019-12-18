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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_NRSSILT_CTRL ; 
 int /*<<< orphan*/  B43_PHY_NRSSILT_DATA ; 
 int /*<<< orphan*/  b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s16 b43_nrssi_hw_read(struct b43_wldev *dev, u16 offset)
{
	u16 val;

	b43_phy_write(dev, B43_PHY_NRSSILT_CTRL, offset);
	val = b43_phy_read(dev, B43_PHY_NRSSILT_DATA);

	return (s16) val;
}
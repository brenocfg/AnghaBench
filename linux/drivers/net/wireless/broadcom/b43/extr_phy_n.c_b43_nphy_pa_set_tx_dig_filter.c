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
 int /*<<< orphan*/  B43_PHY_N (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void b43_nphy_pa_set_tx_dig_filter(struct b43_wldev *dev, u16 offset,
					  const s16 *filter)
{
	int i;

	offset = B43_PHY_N(offset);

	for (i = 0; i < 15; i++, offset++)
		b43_phy_write(dev, offset, filter[i]);
}
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
typedef  int u8 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPTAB16 (int /*<<< orphan*/ ,int) ; 
 int b43_lptab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 lpphy_get_bb_mult(struct b43_wldev *dev)
{
	return (b43_lptab_read(dev, B43_LPTAB16(0, 87)) & 0xFF00) >> 8;
}
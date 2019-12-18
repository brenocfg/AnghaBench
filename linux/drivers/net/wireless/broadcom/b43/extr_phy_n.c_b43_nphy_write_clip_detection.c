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

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_C1_CLIP1THRES ; 
 int /*<<< orphan*/  B43_NPHY_C2_CLIP1THRES ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void b43_nphy_write_clip_detection(struct b43_wldev *dev,
					  const u16 *clip_st)
{
	b43_phy_write(dev, B43_NPHY_C1_CLIP1THRES, clip_st[0]);
	b43_phy_write(dev, B43_NPHY_C2_CLIP1THRES, clip_st[1]);
}
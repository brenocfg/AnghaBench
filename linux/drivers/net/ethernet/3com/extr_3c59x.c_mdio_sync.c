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
struct vortex_private {int dummy; } ;

/* Variables and functions */
 int MDIO_DATA_WRITE1 ; 
 int MDIO_SHIFT_CLK ; 
 int /*<<< orphan*/  Wn4_PhysicalMgmt ; 
 int /*<<< orphan*/  mdio_delay (struct vortex_private*) ; 
 int /*<<< orphan*/  window_write16 (struct vortex_private*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdio_sync(struct vortex_private *vp, int bits)
{
	/* Establish sync by sending at least 32 logic ones. */
	while (-- bits >= 0) {
		window_write16(vp, MDIO_DATA_WRITE1, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		window_write16(vp, MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	}
}
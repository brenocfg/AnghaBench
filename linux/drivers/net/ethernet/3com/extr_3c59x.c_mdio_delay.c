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
 int /*<<< orphan*/  Wn4_PhysicalMgmt ; 
 int /*<<< orphan*/  window_read32 (struct vortex_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdio_delay(struct vortex_private *vp)
{
	window_read32(vp, 4, Wn4_PhysicalMgmt);
}
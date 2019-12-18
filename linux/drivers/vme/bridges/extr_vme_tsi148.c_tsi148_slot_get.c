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
typedef  int u32 ;
struct vme_bridge {struct tsi148_driver* driver_priv; } ;
struct tsi148_driver {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TSI148_LCSR_VSTAT ; 
 int TSI148_LCSR_VSTAT_GA_M ; 
 int geoid ; 
 int ioread32be (scalar_t__) ; 

__attribute__((used)) static int tsi148_slot_get(struct vme_bridge *tsi148_bridge)
{
	u32 slot = 0;
	struct tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	if (!geoid) {
		slot = ioread32be(bridge->base + TSI148_LCSR_VSTAT);
		slot = slot & TSI148_LCSR_VSTAT_GA_M;
	} else
		slot = geoid;

	return (int)slot;
}
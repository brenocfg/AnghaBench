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
typedef  unsigned int u32 ;
struct emac_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_FTR_EMAC4 ; 
 scalar_t__ emac_has_feature (struct emac_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 emac_calc_rwmr(struct emac_instance *dev,
				 unsigned int low, unsigned int high)
{
	if (emac_has_feature(dev, EMAC_FTR_EMAC4))
		return (low << 22) | ( (high & 0x3ff) << 6);
	else
		return (low << 23) | ( (high & 0x1ff) << 7);
}
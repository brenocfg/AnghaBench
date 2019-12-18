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
struct emac_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_FTR_STACR_OC_INVERT ; 
 int EMAC_STACR_OC ; 
 scalar_t__ emac_has_feature (struct emac_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int emac_phy_done(struct emac_instance *dev, u32 stacr)
{
	int done = !!(stacr & EMAC_STACR_OC);

	if (emac_has_feature(dev, EMAC_FTR_STACR_OC_INVERT))
		done = !done;

	return done;
}